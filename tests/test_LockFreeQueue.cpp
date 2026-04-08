#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include "BufferSize.hpp"
#include <gtest/gtest.h>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <thread>
#include <vector>

TEST(QueueTest, AppendSingleMessageToLockFreeQueue) {}

TEST(QueueTest, LockFreeQueueCreatesOrOpensSharedMemory) {
  LockFreeQueueBuilder *lockFreeQueueBuilder = CreateLockFreeQueueBuilder();
  BuildFilePath(lockFreeQueueBuilder, "/queue_shred_memory",
                BufferSize(std::size_t{20}));
  BuildSize(lockFreeQueueBuilder, BufferSize(std::size_t{8}));
  LockFreeQueue *lockFreeQueue = CreateQueue(lockFreeQueueBuilder);

  EXPECT_NE(lockFreeQueue, nullptr);

  DestroyQueue(lockFreeQueue);
  DestroyLockFreeQueueBuilder(lockFreeQueueBuilder);
}

TEST(QueueTest, CreateSharedMemoryCreatesSizedObject) {
  constexpr char kFilePath[] = "/lock_free_queue_shared_memory_test";

  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();
  BuildFilePath(queueBuilder, kFilePath, BufferSize(std::size_t{sizeof(kFilePath)}));
  BuildSize(queueBuilder, BufferSize(std::size_t{32}));

  LockFreeQueue *queue = CreateQueue(queueBuilder);
  int fd = CreateSharedMemory(queue);

  ASSERT_NE(fd, -1);

  struct stat fileStat {};
  ASSERT_EQ(fstat(fd, &fileStat), 0);
  EXPECT_EQ(static_cast<std::size_t>(fileStat.st_size), std::size_t{32});

  close(fd);
  shm_unlink(kFilePath);
  DestroyQueue(queue);
  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueTest, CreateSharedMemoryThrowsOnNullQueue) {
  EXPECT_THROW(CreateSharedMemory(nullptr), std::invalid_argument);
}

TEST(QueueTest, ConcurrentAppendAndDequeueOnSharedQueue) {
  constexpr char kFilePath[] = "/lock_free_queue_append_dequeue_stress";
  constexpr std::size_t kThreadCount = 24;
  constexpr std::size_t kMessageCount = 64;
  constexpr std::size_t kIterationsPerThread = 500;
  const BufferSize messageSize = GetMessageSize();
  const std::size_t totalMessageBytes = kMessageCount * messageSize.get();

  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();
  BuildFilePath(queueBuilder, kFilePath,
                BufferSize(std::size_t{sizeof(kFilePath)}));
  BuildSize(queueBuilder, BufferSize(std::size_t{totalMessageBytes}));

  LockFreeQueue *queue = CreateQueue(queueBuilder);
  int fd = CreateSharedMemory(queue);

  ASSERT_NE(fd, -1);

  void *mapped = mmap(nullptr, totalMessageBytes,
                      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  ASSERT_NE(mapped, MAP_FAILED);

  SetMessageContainer(queue, reinterpret_cast<Message *>(mapped));

  std::vector<Message *> messages(kMessageCount, nullptr);
  for (std::size_t index = 0; index < kMessageCount; ++index) {
    messages[index] = CreateMessage();
    SetSequenceNumber(messages[index], static_cast<unsigned int>(index));
    SetValue(messages[index], static_cast<unsigned int>(index + 1));
  }

  std::atomic<bool> start{false};
  std::vector<unsigned char> threadSucceeded(kThreadCount, 0);
  std::vector<std::thread> threads;
  threads.reserve(kThreadCount);

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    threads.emplace_back([&, index]() {
      while (!start.load(std::memory_order_acquire)) {
        std::this_thread::yield();
      }

      unsigned char succeeded = 1;

      try {
        if ((index % 2) == 0) {
          for (std::size_t iteration = 0; iteration < kIterationsPerThread;
               ++iteration) {
            std::size_t messageIndex = (index + iteration) % kMessageCount;
            (void)AppendTo(queue, messages[messageIndex]);
          }
        } else {
          for (std::size_t iteration = 0; iteration < kIterationsPerThread;
               ++iteration) {
            (void)DequeueFrom(queue);
          }
        }
      } catch (...) {
        succeeded = 0;
      }

      threadSucceeded[index] = succeeded;
    });
  }

  start.store(true, std::memory_order_release);

  for (std::thread &thread : threads) {
    thread.join();
  }

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    EXPECT_EQ(threadSucceeded[index], 1);
  }

  for (Message *&message : messages) {
    DestroyMessage(message);
  }

  munmap(mapped, totalMessageBytes);
  close(fd);
  shm_unlink(kFilePath);
  DestroyQueue(queue);
  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueTest, ConcurrentCreateDestroyAndSharedMemoryLifecycle) {
  constexpr std::size_t kThreadCount = 16;
  constexpr std::size_t kIterationsPerThread = 64;

  std::atomic<bool> start{false};
  std::vector<unsigned char> threadSucceeded(kThreadCount, 0);
  std::vector<std::thread> threads;
  threads.reserve(kThreadCount);

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    threads.emplace_back([&, index]() {
      while (!start.load(std::memory_order_acquire)) {
        std::this_thread::yield();
      }

      unsigned char succeeded = 1;

      try {
        for (std::size_t iteration = 0; iteration < kIterationsPerThread;
             ++iteration) {
          LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

          char filePath[128];
          std::snprintf(filePath, sizeof(filePath),
                        "/lock_free_queue_lifecycle_%zu_%zu", index, iteration);

          BuildFilePath(queueBuilder, filePath,
                        BufferSize(std::size_t{std::strlen(filePath) + 1}));
          BuildSize(queueBuilder, GetMessageSize());

          LockFreeQueue *queue = CreateQueue(queueBuilder);
          int fd = CreateSharedMemory(queue);

          if (fd == -1) {
            succeeded = 0;
          } else {
            close(fd);
            shm_unlink(filePath);
          }

          DestroyQueue(queue);
          DestroyLockFreeQueueBuilder(queueBuilder);
        }
      } catch (...) {
        succeeded = 0;
      }

      threadSucceeded[index] = succeeded;
    });
  }

  start.store(true, std::memory_order_release);

  for (std::thread &thread : threads) {
    thread.join();
  }

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    EXPECT_EQ(threadSucceeded[index], 1);
  }
}

TEST(QueueTest, CreateAndDestroyQueueFromMultipleThreads) {
  constexpr char kFilePath[] = "/tmp/lock_free_queue_thread_test";
  constexpr std::size_t kThreadCount = 8;
  std::vector<unsigned char> threadSucceeded(kThreadCount, 0);

  auto worker = [&](std::size_t index) {
    unsigned char succeeded = 0;
    try {
      LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();
      BuildFilePath(queueBuilder, kFilePath,
                    BufferSize(std::size_t{sizeof(kFilePath)}));
      BuildSize(queueBuilder, BufferSize(std::size_t{16}));

      LockFreeQueue *queue = CreateQueue(queueBuilder);
      succeeded = queue != nullptr ? 1 : 0;

      DestroyQueue(queue);
      DestroyLockFreeQueueBuilder(queueBuilder);
    } catch (...) {
      succeeded = 0;
    }
    threadSucceeded[index] = succeeded;
  };

  std::vector<std::thread> threads;
  threads.reserve(kThreadCount);
  for (std::size_t index = 0; index < kThreadCount; ++index) {
    threads.emplace_back(worker, index);
  }

  for (std::thread &thread : threads) {
    thread.join();
  }

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    EXPECT_EQ(threadSucceeded[index], 1);
  }
}

TEST(QueueTest, QueueAccessorsWorkInParallelOnIndependentQueues) {
  constexpr char kFilePath[] = "/tmp/lock_free_queue_accessor_test";
  constexpr std::size_t kThreadCount = 6;
  std::vector<unsigned char> threadSucceeded(kThreadCount, 0);

  auto worker = [&](std::size_t index) {
    unsigned char succeeded = 0;
    try {
      LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();
      BuildFilePath(queueBuilder, kFilePath,
                    BufferSize(std::size_t{sizeof(kFilePath)}));
      BuildSize(queueBuilder, BufferSize(std::size_t{index + 2}));

      LockFreeQueue *queue = CreateQueue(queueBuilder);
      const char *filePath = GetFilePath(queue);

      if (queue != nullptr && filePath != nullptr &&
          std::strcmp(filePath, kFilePath) == 0) {
        SetMessageContainer(queue, nullptr);
        SetEnqueueCell(queue, nullptr);
        SetDequeueCell(queue, nullptr);

        if (GetMessageContainer(queue) == nullptr &&
            GetEnqueueCell(queue) == nullptr &&
            GetDequeueCell(queue) == nullptr &&
            GetMessageContainerLength(queue).get() == index + 2) {
          succeeded = 1;
        }
      }

      DestroyQueue(queue);
      DestroyLockFreeQueueBuilder(queueBuilder);
    } catch (...) {
      succeeded = 0;
    }
    threadSucceeded[index] = succeeded;
  };

  std::vector<std::thread> threads;
  threads.reserve(kThreadCount);
  for (std::size_t index = 0; index < kThreadCount; ++index) {
    threads.emplace_back(worker, index);
  }

  for (std::thread &thread : threads) {
    thread.join();
  }

  for (std::size_t index = 0; index < kThreadCount; ++index) {
    EXPECT_EQ(threadSucceeded[index], 1);
  }
}

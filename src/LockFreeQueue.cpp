#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include "Message.hpp"

#include <fcntl.h>
#include <stdexcept>
#include <sys/mman.h>
#include <unistd.h>

struct LockFreeQueue {
  Message *messageContainer;
  BufferSize messageContainerLength;

  const char *filePath;
  // Compare and swap these
  Message *enqueueCell;
  Message *dequeueCell;
};

/*
sequence numbers are used to determine the state of the cell and what wrap cycle
the producers and soncumers are on
*/

LockFreeQueue *CreateQueue(const LockFreeQueueBuilder *builder) {
  // @ Add these to the builder class, so we don't ahve to build with nullptr
  return new LockFreeQueue{nullptr, GetSize(builder), GetFilePath(builder),
                           nullptr, nullptr};
}

LockFreeQueueResult AppendTo(LockFreeQueue *queue, const Message *message) {}
LockFreeQueueResult DequeueFrom(LockFreeQueue *queue) {}

int CreateSharedMemory(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to CreateSharedMemory");
  }

  int fd = shm_open(GetFilePath(queue), O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    throw std::runtime_error("shm_open failed in CreateSharedMemory");
  }

  // This API is inconvenient, but BufferSize is the queue's size type.
  if (ftruncate(fd, static_cast<off_t>(
                        GetMessageContainerLength(queue).get())) == -1) {
    close(fd);
    throw std::runtime_error("ftruncate failed in CreateSharedMemory");
  }

  return fd;
}

LockFreeQueueResult DestroyQueue(LockFreeQueue *&queue) {
  delete queue;
  queue = nullptr;
  return LockFreeQueueResult::Destroyed;
}

Message *GetMessageContainer(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to GetMessageContainer");
  }
  return queue->messageContainer;
}

void SetMessageContainer(LockFreeQueue *queue, Message *messageContainer) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to SetMessageContainer");
  }
  queue->messageContainer = messageContainer;
}

BufferSize GetMessageContainerLength(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to GetMessageContainerLength");
  }
  return queue->messageContainerLength;
}

void SetMessageContainerLength(LockFreeQueue *queue,
                               BufferSize messageContainerLength) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to SetMessageContainerLength");
  }
  queue->messageContainerLength = messageContainerLength;
}

const char *GetFilePath(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument("Queue is nullptr when passed to GetFilePath");
  }
  return queue->filePath;
}

void SetFilePath(LockFreeQueue *queue, const char *filePath) {
  if (queue == nullptr) {
    throw std::invalid_argument("Queue is nullptr when passed to SetFilePath");
  }
  queue->filePath = filePath;
}

Message *GetEnqueueCell(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to GetEnqueueCell");
  }
  return queue->enqueueCell;
}

void SetEnqueueCell(LockFreeQueue *queue, Message *enqueueCell) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to SetEnqueueCell");
  }
  queue->enqueueCell = enqueueCell;
}

Message *GetDequeueCell(LockFreeQueue *queue) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to GetDequeueCell");
  }
  return queue->dequeueCell;
}

void SetDequeueCell(LockFreeQueue *queue, Message *dequeueCell) {
  if (queue == nullptr) {
    throw std::invalid_argument(
        "Queue is nullptr when passed to SetDequeueCell");
  }
  queue->dequeueCell = dequeueCell;
}

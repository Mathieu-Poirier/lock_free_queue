#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include "BufferSize.hpp"
#include <fcntl.h> 
#include <gtest/gtest.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <unistd.h>   

TEST(QueueTest, AppendSingleMessageToLockFreeQueue) {}

TEST(QueueTest, LockFreeQueueCreatesOrOpensSharedMemory) {
  LockFreeQueueBuilder *lockFreeQueueBuilder = CreateLockFreeQueueBuilder();
  BuildFilePath(lockFreeQueueBuilder, "/queue_shred_memory", BufferSize(20uz));
  LockFreeQueue *lockFreeQueue = CreateQueue(lockFreeQueueBuilder);
}
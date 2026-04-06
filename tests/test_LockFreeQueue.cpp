#include "LockFreeQueueBuilder.hpp"
#include "LockFreeQueue.hpp"
#include <gtest/gtest.h>

TEST(QueueTest, AppendSingleMessageToLockFreeQueue) {}

TEST(QueueTest, LockFreeQueueCreatesOrOpensSharedMemory) {
  LockFreeQueueBuilder* lockFreeQueueBuilder = CreateLockFreeQueueBuilder();
  LockFreeQueue* lockFreeQueue = CreateQueue(lockFreeQueueBuilder);
}
#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"
#include <iostream>
#include <stdexcept>

int main() {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();
  // BuildSize(queueBuilder, 0);
  // DestroyLockFreeQueueBuilder(queueBuilder);
  return 0;
}
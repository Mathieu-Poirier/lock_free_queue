#include <iostream>
#include <stdexcept>
#include "LockFreeQueue.hpp"
#include "LockFreeQueueBuilder.hpp"

int main() {
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    // BuildSize(queueBuilder, 0);
    // DestroyLockFreeQueueBuilder(queueBuilder);
    return 0;
}
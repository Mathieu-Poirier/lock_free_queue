#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include "LockFreeQueueBuilder.hpp"

enum class LockFreeQueueResult {
    Destroyed,
    AppendSuccess,
    Full,
    Empty,
};

struct LockFreeQueue;

// @ For C-style opaque we usually just use pointers
// @ Type should maybe just be uint64_t
LockFreeQueue* CreateQueue(const LockFreeQueueBuilder* builder);
LockFreeQueueResult DestroyQueue(LockFreeQueue queue);
LockFreeQueueResult AppendTo(LockFreeQueue* queue, uint64_t value);


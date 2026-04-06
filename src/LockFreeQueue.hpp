#pragma once
#include "LockFreeQueueBuilder.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

enum class LockFreeQueueResult {
  Destroyed,
  AppendSuccess,
  Full,
  Empty,
};

// MWMR Data Structure
struct LockFreeQueue;

// @ For C-style opaque we usually just use pointers
// @ Type should maybe just be uint64_t
// @ No it'll be the Message data structure
// Creating the Queue will fopen the file stream and read or write based on a
// flag? Maybe we need to decouple those from this data structure though or is
// the Reader/Writer making the data structure? Maybe have a file called the
// same thing every time with some sort of id of where the data file is to be
// written and it's taken like from the CLI part of the profroam and new readers
// / writers temporarily open it

// Since we have the file encapsulated from the builder
LockFreeQueue *CreateQueue(const LockFreeQueueBuilder *builder);
LockFreeQueueResult DestroyQueue(LockFreeQueue queue);
// LockFreeQueueResult AppendTo(LockFreeQueue* queue, uint64_t value);

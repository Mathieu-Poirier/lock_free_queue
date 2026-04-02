#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include "LockFreeQueueBuilder.hpp"

struct LockFreeQueue;

LockFreeQueue* CreateQueue(const LockFreeQueueBuilder* builder);
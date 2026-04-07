#pragma once

#include "BufferSize.hpp"

struct LockFreeQueueBuilder;

void LockFreeQueueBuilderInitialize(LockFreeQueueBuilder *lockFreeQueueBuilder);

LockFreeQueueBuilder *CreateLockFreeQueueBuilder();
void DestroyLockFreeQueueBuilder(LockFreeQueueBuilder *&lockFreeQueueBuilder);

void BuildSize(LockFreeQueueBuilder *lockFreeQueueBuilder,
               const BufferSize size);
void BuildFilePath(LockFreeQueueBuilder *lockFreeQueueBuilder,
                   const char *filePath, const BufferSize filePathLenght);

[[nodiscard]] BufferSize GetSize(const LockFreeQueueBuilder *lockFreeQueueBuilder);
[[nodiscard]] const char *GetFilePath(
    const LockFreeQueueBuilder *lockFreeQueueBuilder);

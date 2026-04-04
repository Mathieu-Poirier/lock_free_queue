#pragma once

struct LockFreeQueueBuilder;

void LockFreeQueueBuilderInitialize(LockFreeQueueBuilder* lockFreeQueueBuilder);

LockFreeQueueBuilder* CreateLockFreeQueueBuilder();
void DestroyLockFreeQueueBuilder(LockFreeQueueBuilder*& lockFreeQueueBuilder);

void BuildSize(LockFreeQueueBuilder* lockFreeQueueBuilder, std::size_t size);
void BuildFilePath(LockFreeQueueBuilder* lockFreeQueueBuilder, const char* filePath);
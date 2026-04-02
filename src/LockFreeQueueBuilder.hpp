#pragma once

struct LockFreeQueueBuilder;

void LockFreeQueueBuilderInitialize(LockFreeQueueBuilder* lockFreeQueueBuilder);

LockFreeQueueBuilder* CreateLockFreeQueueBuilder();
void DestroyLockFreeQueueBuilder(LockFreeQueueBuilder*& lockFreeQueueBuilder);

void BuildSize(LockFreeQueueBuilder* lockFreeQueueBuilder, std::size_t size);
void BuildPath(LockFreeQueueBuilder* lockFreeQueueBuilder, const char* shm_name);
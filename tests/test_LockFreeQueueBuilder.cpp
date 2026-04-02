#include <gtest/gtest.h>
#include <stdexcept>
#include "LockFreeQueueBuilder.hpp"

TEST(QueueBuilderTest, CreateQueueBuilderWithZeroSize){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    EXPECT_THROW(BuildSize(queueBuilder, 0uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, CreateQueueBuilderWithSizeBiggerThanMaxSize){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    EXPECT_THROW(BuildSize(queueBuilder, -1), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}



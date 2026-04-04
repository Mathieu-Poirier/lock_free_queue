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

TEST(QueueBuilderTest, PassInNullPtrToQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    EXPECT_THROW(BuildFilePath(queueBuilder, nullptr, 0uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, EmptyPathQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    EXPECT_THROW(BuildFilePath(queueBuilder, "", 0uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, NoNullTerminatorQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    char buf[] = {'a', 'b', 'c'};
    const char* p = buf;
    EXPECT_THROW(BuildFilePath(queueBuilder, buf, 3uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathLength4097AndArbitraryBufferQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    char buf[] = {'a', 'b', 'c'};
    const char* p = buf;
    EXPECT_THROW(BuildFilePath(queueBuilder, buf, 4097uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathOverMaxLengthAndArbitraryBufferQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    char buf[] = {'a', 'b', 'c'};
    const char* p = buf;
    EXPECT_THROW(BuildFilePath(queueBuilder, buf, -1), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathZeroSizeAndArbitraryBufferQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    char buf[] = {'a', 'b', 'c'};
    const char* p = buf;
    EXPECT_THROW(BuildFilePath(queueBuilder, buf, 0uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

// @ Maybe santinize bytes like /n /t
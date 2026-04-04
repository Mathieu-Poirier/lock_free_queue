#include <gtest/gtest.h>
#include <stdexcept>
#include "LockFreeQueueBuilder.hpp"

// Size
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

// Filepath
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

// This one is a little weird too, we should add some UB checks
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

TEST(QueueBuilderTest, PathZeroLengthAndArbitraryBufferQueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    char buf[] = {'a', 'b', 'c'};
    const char* p = buf;
    EXPECT_THROW(BuildFilePath(queueBuilder, buf, 0uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathLengthDoesNotMatchBufferLengthSmaller_QueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    const char* str_buf = "Hello";
    EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, 5uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}


TEST(QueueBuilderTest, PathLengthDoesNotMatchBufferLengthLarger_QueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    const char* str_buf = "Hello";
    EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, 7uz), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathLengthParameterIsOverLimit_QueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    const char* str_buf = "Hello";
    EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, 4097), std::invalid_argument);
    DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, RealPathDoesNotThrow_QueueBuilderBuildFilePath){
    LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
    EXPECT_NO_THROW(BuildFilePath(queueBuilder, "AAAAAAA", 8));
    DestroyLockFreeQueueBuilder(queueBuilder);
}

// TEST(QueueBuilderTest, PathBufferLenghtIsOverLimit_QueueBuilderBuildFilePath){
//     LockFreeQueueBuilder* queueBuilder = CreateLockFreeQueueBuilder();
//     char str_buf[4098]{};
//     for(auto i{0uz}; i < 4097; i++){
//         str_buf[i] = 'A';
//     }
//     EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, 4096), std::invalid_argument);
//     DestroyLockFreeQueueBuilder(queueBuilder);
// }


// @ Maybe santinize bytes like /n /t
#include <gtest/gtest.h>
#include <stdexcept>

#include "BufferSize.hpp"
#include "LockFreeQueueBuilder.hpp"

TEST(QueueBuilderTest, PassInNullPtrToBuildFilePathThrows) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  EXPECT_THROW(BuildFilePath(queueBuilder, nullptr, BufferSize(std::size_t{1})),
               std::invalid_argument);

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, EmptyPathWithLengthOneDoesNotThrow) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  EXPECT_NO_THROW(BuildFilePath(queueBuilder, "", BufferSize(std::size_t{1})));

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, NoNullTerminatorThrows) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  char buf[] = {'a', 'b', 'c'};

  EXPECT_THROW(BuildFilePath(queueBuilder, buf, BufferSize(std::size_t{3})),
               std::invalid_argument);

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathLengthSmallerThanCStringLengthThrows) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  const char *str_buf = "Hello";

  EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, BufferSize(std::size_t{5})),
               std::invalid_argument);

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, PathLengthLargerThanCStringLengthThrows) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  const char *str_buf = "Hello";

  EXPECT_THROW(BuildFilePath(queueBuilder, str_buf, BufferSize(std::size_t{7})),
               std::invalid_argument);

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, RealPathDoesNotThrow) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  EXPECT_NO_THROW(
      BuildFilePath(queueBuilder, "AAAAAAA", BufferSize(std::size_t{8})));

  DestroyLockFreeQueueBuilder(queueBuilder);
}

TEST(QueueBuilderTest, ValidBuildSizeDoesNotThrow) {
  LockFreeQueueBuilder *queueBuilder = CreateLockFreeQueueBuilder();

  EXPECT_NO_THROW(BuildSize(queueBuilder, BufferSize(std::size_t{8})));

  DestroyLockFreeQueueBuilder(queueBuilder);
}
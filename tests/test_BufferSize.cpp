#include <gtest/gtest.h>
#include <stdexcept>

#include "BufferSize.hpp"

TEST(BufferSizeTest, ConstructWithZeroThrows) {
  EXPECT_THROW(BufferSize(std::size_t{0}), std::invalid_argument);
}

TEST(BufferSizeTest, ConstructOverMaxThrows) {
  EXPECT_THROW(BufferSize(std::size_t{4097}), std::invalid_argument);
}

TEST(BufferSizeTest, ConstructValidValueDoesNotThrow) {
  EXPECT_NO_THROW(BufferSize(std::size_t{1}));
  EXPECT_NO_THROW(BufferSize(std::size_t{64}));
  EXPECT_NO_THROW(BufferSize(std::size_t{4096}));
}

TEST(BufferSizeTest, GetReturnsConstructedValue) {
  BufferSize size(std::size_t{123});
  EXPECT_EQ(size.get(), std::size_t{123});
}

TEST(BufferSizeTest, SetZeroThrows) {
  BufferSize size(std::size_t{10});
  EXPECT_THROW(size.set(std::size_t{0}), std::invalid_argument);
}

TEST(BufferSizeTest, SetOverMaxThrows) {
  BufferSize size(std::size_t{10});
  EXPECT_THROW(size.set(std::size_t{4097}), std::invalid_argument);
}

TEST(BufferSizeTest, SetValidValueUpdatesStoredValue) {
  BufferSize size(std::size_t{10});
  EXPECT_NO_THROW(size.set(std::size_t{128}));
  EXPECT_EQ(size.get(), std::size_t{128});
}

TEST(BufferSizeTest, SetFromOtherBufferSizeCopiesValue) {
  BufferSize a(std::size_t{10});
  BufferSize b(std::size_t{256});

  EXPECT_NO_THROW(a.set(b));
  EXPECT_EQ(a.get(), std::size_t{256});
}
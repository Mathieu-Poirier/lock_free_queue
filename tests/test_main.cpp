#include <gtest/gtest.h>
#include "queue.hpp"

TEST(QueueTest, AddWorks) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_NE(add(2, 2), 5);
}
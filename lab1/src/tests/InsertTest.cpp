#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(InsertTests, Insert1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.Insert(0, 20), std::out_of_range);
}

TEST(InsertTests, Insert2) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.Insert(10, 20), std::out_of_range);
}

TEST(InsertTests, Insert3) {
    CircularBuffer<int> cb(5);
    EXPECT_NO_THROW(cb.Insert(0, 20));
}

TEST(InsertTests, Insert4) {
    CircularBuffer<int> cb(5);
    cb.PushBack(1);
    cb.PushBack(2); // Expected: 1 (front) 2 (back) _ _ _

    cb.Insert(1, 3); // Expected: 1 (front) 3 2 (back) _ _
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 2);
    EXPECT_EQ(cb[1], 3);
}

TEST(InsertTests, Insert5) {
    CircularBuffer<int> cb(5);

    cb.Insert(0, 3); // Expected: 3 (front, back) _ _ _ _
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 3);
    EXPECT_EQ(cb.back(), 3);
}

TEST(InsertTests, Insert6) {
    CircularBuffer<int> cb(5, 0);
    cb[1] = 1;
    cb[4] = 4; // Expected: 0 (front) 1 0 0 4 (back)

    cb.Insert(2, 3); // Expected: 4 (back) 1 (front) 3 0 0
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_EQ(cb[1], 3);
}

TEST(InsertTests, Insert7) {
    CircularBuffer<int> cb(5, 0);
    cb[1] = 1; // Expected: 0 (front) 1 0 0 0 (back)

    cb.Insert(5, 3); // Expected: 3 (back) 1 (front) 0 0 0
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 3);
}

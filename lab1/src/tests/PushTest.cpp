#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(PushTests, PushBack1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.PushBack(10), std::out_of_range);
}

TEST(PushTests, PushBack2) {
    CircularBuffer<int> cb(5);
    cb.PushBack(10);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PushTests, PushBack3) {
    CircularBuffer<int> cb(5);
    cb.PushBack(10);
    cb.PushBack(15); // Expected: 10 (front) 15 (back) _ _ _
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.back(), 15);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PushTests, PushBack4) {
    CircularBuffer<int> cb(5, 10); // Expected: 10 (front) 10 10 10 10 (back)
    cb[1] = 20; // Expected: 10 (front) 20 10 10 10 (back)
    cb.PushBack(15); // Expected: 15 (back) 20 (front) 10 10 10
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.back(), 15);
    EXPECT_EQ(cb.front(), 20);
}

TEST(PushTests, PushFront1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.PushFront(10), std::out_of_range);
}

TEST(PushTests, PushFront2) {
    CircularBuffer<int> cb(5);
    cb.PushFront(10);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.front(), 10);
    EXPECT_EQ(cb.back(), 10);
}

TEST(PushTests, PushFront3) {
    CircularBuffer<int> cb(5);
    cb.PushFront(10);
    cb.PushFront(15); // Expected: _ _ _ 15 (front) 10 (back)
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 15);
    EXPECT_EQ(cb.back(), 10);
}

TEST(PushTests, PushFront4) {
    CircularBuffer<int> cb(5, 10); // Expected: 10 (front) 10 10 10 10 (back)
    cb[3] = 20; // Expected: 10 (front) 10 10 20 10 (back)
    cb.PushFront(15); // Expected: 10 10 10 20 (back) 15 (front)
    EXPECT_EQ(cb.size(), 5);
    EXPECT_EQ(cb.front(), 15);
    EXPECT_EQ(cb.back(), 20);
}

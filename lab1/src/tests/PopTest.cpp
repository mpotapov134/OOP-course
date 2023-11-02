#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(PopTests, PopBack1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.PopBack(), std::out_of_range);
}

TEST(PopTests, PopBack2) {
    CircularBuffer<int> cb(5);
    cb.PushBack(10);
    int item = cb.PopBack();
    EXPECT_EQ(item, 10);
    EXPECT_EQ(cb.IsEmpty(), true);
}

TEST(PopTests, PopBack3) {
    CircularBuffer<int> cb(5);
    cb.PushBack(10);
    cb.PushBack(15); // Expected: 10 (front) 15 (back) _ _ _
    int item = cb.PopBack(); // Expected: 10 (front, back) _ _ _ _
    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PopTests, PopBack4) {
    CircularBuffer<int> cb(5, 10); // Expected: 10 (front) 10 10 10 10 (back)
    cb[1] = 1;
    cb[4] = 4;
    cb.PushBack(15); // Expected: 15 (back) 1 (front) 10 10 4
    int item = cb.PopBack(); // Expected _ 1 (front) 10 10 4 (back)
    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb.back(), 4);
    EXPECT_EQ(cb.front(), 1);
}

TEST(PopTests, PopFront1) {
    CircularBuffer<int> cb;
    EXPECT_THROW(cb.PopFront(), std::out_of_range);
}

TEST(PopTests, PopFront2) {
    CircularBuffer<int> cb(5);
    cb.PushFront(10);
    int item = cb.PopFront();
    EXPECT_EQ(item, 10);
    EXPECT_EQ(cb.IsEmpty(), true);
}

TEST(PopTests, PopFront3) {
    CircularBuffer<int> cb(5);
    cb.PushFront(10);
    cb.PushFront(15); // Expected: _ _ _ 15 (front) 10 (end)
    int item = cb.PopFront(); // Expected: _ _ _ _ 10 (front, end)
    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb.back(), 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(PopTests, PopFront4) {
    CircularBuffer<int> cb(5, 10); // Expected: 10 (front) 10 10 10 10 (back)
    cb[0] = 0;
    cb[3] = 3;
    cb.PushFront(15); // Expected: 0 10 10 3 (end) 15 (front)
    int item = cb.PopFront(); // Expected 0 (front) 10 10 3 (end) _
    EXPECT_EQ(item, 15);
    EXPECT_EQ(cb.size(), 4);
    EXPECT_EQ(cb.back(), 3);
    EXPECT_EQ(cb.front(), 0);
}

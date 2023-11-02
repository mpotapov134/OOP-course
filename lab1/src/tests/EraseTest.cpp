#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(EraseTests, Erase1) {
    CircularBuffer<int> cb(10, 10);
    EXPECT_THROW(cb.Erase(10, 20), std::out_of_range);
}

TEST(EraseTests, Erase2) {
    CircularBuffer<int> cb(10, 10);
    EXPECT_THROW(cb.Erase(5, 20), std::out_of_range);
}

TEST(EraseTests, Erase3) {
    CircularBuffer<int> cb(10, 10);
    EXPECT_NO_THROW(cb.Erase(5, 10));
}

TEST(EraseTests, Erase4) {
    CircularBuffer<int> cb(10, 10);
    cb.Erase(5, 2);
    EXPECT_EQ(cb.size(), 10);
}

TEST(EraseTests, Erase5) {
    CircularBuffer<int> cb(5);
    cb.PushBack(1);
    cb.PushBack(2);
    cb.PushBack(3);
    cb.PushBack(4);
    cb.PushBack(5); // Expected: 1 (front) 2 3 4 5 (back)

    cb.Erase(2, 4); // Expected: 1 (front) 2 5 (back) _ _
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb.front(), 1);
    EXPECT_EQ(cb.back(), 5);
    EXPECT_EQ(cb[1], 2);
}

TEST(EraseTests, Erase6) {
    CircularBuffer<int> cb(5);
    cb.PushBack(1);
    cb.PushBack(2);
    cb.PushBack(3);
    cb.PushBack(4);
    cb.PushBack(5); // Expected: 1 (front) 2 3 4 5 (back)

    cb.Erase(0, 3); // Expected: 4 (front) 5 (back) _ _ _
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb.front(), 4);
    EXPECT_EQ(cb.back(), 5);
}

TEST(EraseTests, Erase7) {
    CircularBuffer<int> cb(5, 10);
    cb.Erase(0, 5);
    EXPECT_EQ(cb.size(), 0);
}

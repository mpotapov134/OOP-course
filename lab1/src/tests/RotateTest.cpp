#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(RotateTests, Linearize1) {
    CircularBuffer<int> cb;
    EXPECT_EQ(cb.Linearize(), nullptr);
}

TEST(RotateTests, Linearize2) {
    CircularBuffer<int> cb(4);
    cb.PushBack(1);
    cb.PushBack(2);
    cb.PushBack(3);
    cb.PushBack(4);
    cb.PushBack(5);
    cb.PushBack(6); // Expected: 5 6 (back) 3 (front) 4

    int* buffer = cb.buffer();
    EXPECT_EQ(buffer[0], 5);
    EXPECT_EQ(buffer[1], 6);
    EXPECT_EQ(buffer[2], 3);
    EXPECT_EQ(buffer[3], 4);

    cb.Linearize(); // Expected: 3 (front) 4 5 6 (back)
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 5);
    EXPECT_EQ(buffer[3], 6);
}

TEST(RotateTests, Rotate1) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.Rotate(0), std::out_of_range);
}

TEST(RotateTests, Rotate2) {
    CircularBuffer<int> cb(5, 10);
    cb.PopBack();
    EXPECT_THROW(cb.Rotate(4), std::out_of_range);
}

TEST(RotateTests, Rotate3) {
    CircularBuffer<int> cb(4);
    cb.PushBack(1);
    cb.PushBack(2);
    cb.PushBack(3);
    cb.PushBack(4); // Expected: 1 (front) 2 3 4 (back)
    int old_front = cb.front();
    int old_back = cb.back();

    cb.Rotate(2); // Expected: 3 4 (back) 1 (front) 2
    EXPECT_EQ(cb.front(), old_front);
    EXPECT_EQ(cb.back(), old_back);

    int* buffer = cb.buffer();
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
    EXPECT_EQ(buffer[2], 1);
    EXPECT_EQ(buffer[3], 2);
}

TEST(RotateTests, Rotate4) {
    CircularBuffer<int> cb(4);
    cb.PushBack(1);
    cb.PushBack(2);
    cb.PushBack(3);
    cb.PushBack(4);
    cb.PushBack(5); // Expected: 5 (back) 2 (front) 3 4
    int old_front = cb.front();
    int old_back = cb.back();

    cb.Rotate(2); // Expected: 4 5 (back) 2 (front) 3
    EXPECT_EQ(cb.front(), old_front);
    EXPECT_EQ(cb.back(), old_back);

    int* buffer = cb.buffer();
    EXPECT_EQ(buffer[0], 4);
    EXPECT_EQ(buffer[1], 5);
    EXPECT_EQ(buffer[2], 2);
    EXPECT_EQ(buffer[3], 3);
}

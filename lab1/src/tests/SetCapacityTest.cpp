#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(SetCapacityTests, SetCapacity1) {
    CircularBuffer<int> cb;
    cb.SetCapacity(10);
    EXPECT_EQ(cb.capacity(), 10);
}

TEST(SetCapacityTests, SetCapacity2) {
    CircularBuffer<int> cb(3, 10);
    cb.SetCapacity(10);
    EXPECT_EQ(cb.capacity(), 10);
    EXPECT_EQ(cb.size(), 3);
    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 10);
    }
}

TEST(SetCapacityTests, SetCapacity3) {
    CircularBuffer<int> cb(5, 10);
    cb.SetCapacity(3);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_EQ(cb.size(), 3);
    for (int i = 0; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 10);
    }
}

TEST(SetCapacityTests, SetCapacity4) {
    CircularBuffer<int> cb(3, 10);
    cb.SetCapacity(0);
    EXPECT_EQ(cb.capacity(), 0);
    EXPECT_EQ(cb.size(), 0);
}

TEST(SetCapacityTests, Resize1) {
    CircularBuffer<int> cb(3, 10);
    int old_size = cb.size();

    cb.Resize(5, 15);
    EXPECT_EQ(cb.capacity(), 5);
    EXPECT_EQ(cb.size(), 5);

    for (int i = 0; i < old_size; i++) {
        EXPECT_EQ(cb[i], 10);
    }
    for (int i = old_size; i < cb.size(); i++) {
        EXPECT_EQ(cb[i], 15);
    }
}

TEST(SetCapacityTests, Resize2) {
    CircularBuffer<int> cb(5, 10);
    int old_size = cb.size();

    cb.Resize(3, 15);
    EXPECT_EQ(cb.capacity(), 3);
    EXPECT_EQ(cb.size(), 3);
    for (int i = 0; i < old_size; i++) {
        EXPECT_EQ(cb[i], 10);
    }
}

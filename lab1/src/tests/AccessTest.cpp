#include <gtest/gtest.h>
#include "../CircularBuffer.h"

TEST(AccessTests, IndexAccess1) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_EQ(cb[3], 10);
}

TEST(AccessTests, IndexAccess2) {
    CircularBuffer<int> cb(5, 10);
    cb[1] = 15;
    EXPECT_EQ(cb[1], 15);
}

TEST(AccessTests, IndexAccess3) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_NO_THROW(cb[100]);
    EXPECT_NO_THROW(cb[-100]);
}

TEST(AccessTests, AtMethod1) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_EQ(cb.at(3), 10);
}

TEST(AccessTests, AtMethod2) {
    CircularBuffer<int> cb(5, 10);
    cb.at(1) = 15;
    EXPECT_EQ(cb.at(1), 15);
}

TEST(AccessTests, AtMethod3) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_THROW(cb.at(100), std::out_of_range);
    EXPECT_THROW(cb.at(-100), std::out_of_range);
}

TEST(AccessTests, AtMethod4) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_THROW(cb.at(5), std::out_of_range);
}

TEST(AccessTests, AtMethod5) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.at(0), std::out_of_range);
}

TEST(AccessTests, FrontMethod1) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_EQ(cb.front(), 10);
}

TEST(AccessTests, FrontMethod2) {
    CircularBuffer<int> cb(5, 10);
    cb.front() = 15;
    EXPECT_EQ(cb.front(), 15);
}

TEST(AccessTests, FrontMethod3) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.front(), std::out_of_range);
}

TEST(AccessTests, BackMethod1) {
    CircularBuffer<int> cb(5, 10);
    EXPECT_EQ(cb.back(), 10);
}

TEST(AccessTests, BackMethod2) {
    CircularBuffer<int> cb(5, 10);
    cb.back() = 15;
    EXPECT_EQ(cb.back(), 15);
}

TEST(AccessTests, BackMethod3) {
    CircularBuffer<int> cb(5);
    EXPECT_THROW(cb.back(), std::out_of_range);
}

#include <gtest/gtest.h>
#include "../src/Universe.h"

TEST(TickTests, test1) {
    std::set<std::pair<int, int>> coords = {{5, 5}};
    std::set<std::pair<int, int>> next_coords = {};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test2) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {6, 6}, {4, 6}, {5, 7}};
    std::set<std::pair<int, int>> next_coords = {{5, 5}, {6, 6}, {4, 6}, {5, 7}};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test3) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {6, 5}, {5, 6}, {6, 6}};
    std::set<std::pair<int, int>> next_coords = {{5, 5}, {6, 5}, {5, 6}, {6, 6}};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test4) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {6, 5}};
    std::set<std::pair<int, int>> next_coords = {};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test5) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {6, 5}, {7, 5}};
    std::set<std::pair<int, int>> next_coords = {{6, 4}, {6, 5}, {6, 6}};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test6) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {6, 5}, {5, 6}};
    std::set<std::pair<int, int>> next_coords = {{5, 5}, {6, 5}, {5, 6}, {6, 6}};
    Universe u(Universe::default_name, Universe::default_b_rule,
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test7) {
    std::set<std::pair<int, int>> coords = {{5, 5}};
    std::set<std::pair<int, int>> next_coords = {{6, 5}, {4, 5}, {5, 4}, {5, 6},
        {4, 4}, {6, 4}, {4, 6}, {6, 6}};
    Universe u(Universe::default_name, {1},
        Universe::default_s_rule, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test8) {
    std::set<std::pair<int, int>> coords = {
        {4, 4}, {4, 5}, {4, 6},
        {5, 4}, {5, 5}, {5, 6},
        {6, 4}, {6, 5}, {6, 6}};
    Universe u(Universe::default_name, {},
        {0, 1, 2, 3, 4, 5, 6, 7, 8}, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), coords);
}

TEST(TickTests, test9) {
    std::set<std::pair<int, int>> coords = {{4, 5}, {5, 5}, {6, 5}, {5, 4}, {5, 6}};
    std::set<std::pair<int, int>> next_coords = {{5, 5}};
    Universe u(Universe::default_name, {4}, {4}, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test10) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {5, 6}, {5, 7}, {6, 5}, {6, 7},
        {7, 5}, {7, 6}, {7, 7}};
    std::set<std::pair<int, int>> next_coords = {{6, 6}};
    Universe u(Universe::default_name, {8}, {}, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test11) {
    std::set<std::pair<int, int>> coords = {{5, 5}, {5, 6}, {5, 7}, {6, 5},
        {7, 5}, {7, 6}, {7, 7}};
    std::set<std::pair<int, int>> next_coords = {{6, 6}, {6, 7}};
    Universe u(Universe::default_name, {4, 7}, {}, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

TEST(TickTests, test12) {
    std::set<std::pair<int, int>> coords = {{1, 1}, {1, 2}, {1, 3},
        {5, 1}, {4, 2}, {5, 2}, {6, 2}, {5, 3},
        {10, 1}, {9, 2}, {10, 2}, {11, 2},
        {20, 1}, {21, 1}, {20, 2}, {21, 2}, {22, 2}, {21, 3}};
    std::set<std::pair<int, int>> next_coords = {{1, 2}, {5, 2}, {9, 2}, {11, 2},
        {21, 1}, {20, 2}};
    Universe u(Universe::default_name, {}, {2, 4}, coords);
    u.Tick();
    EXPECT_EQ(u.coords(), next_coords);
}

#include <gtest/gtest.h>
#include "../parser.h"

using namespace std;

TEST(ParserTest, Split1) {
    string line = "hello";
    list<string> correct = {"hello"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split2) {
    string line = "a b c d";
    list<string> correct = {"a", "b", "c", "d"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split3) {
    string line = "";
    list<string> correct = {};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split4) {
    string line = "#!a-=,b^|;c@*d";
    list<string> correct = {"a", "b", "c", "d"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split5) {
    string line = "1 2 34,56";
    list<string> correct = {"1", "2", "34", "56"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split6) {
    string line = "@#$%^&*(-+=)/|,.<>";
    list<string> correct = {};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split7) {
    string line = "a b c d\n";
    list<string> correct = {"a", "b", "c", "d"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

TEST(ParserTest, Split8) {
    string line = "a\tb\nc\rd";
    list<string> correct = {"a", "b", "c", "d"};
    Parser parser;
    list<string> result = parser.Split(line);
    EXPECT_EQ(result, correct);
}

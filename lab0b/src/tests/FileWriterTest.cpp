#include <gtest/gtest.h>
#include <fstream>
#include "../filewriter.h"

TEST(FileWriterTest, FileIsOpen) {
    FileWriter writer("test.txt");
    EXPECT_EQ(false, writer.FileIsOpen());
}

TEST(FileWriterTest, WriteLine) {
    FileWriter writer("test.txt");
    writer.Open();
    writer.WriteLine("testing");
    writer.Close();

    std::ifstream file("test.txt");
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "testing");
}

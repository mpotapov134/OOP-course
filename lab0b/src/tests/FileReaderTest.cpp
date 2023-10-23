#include <gtest/gtest.h>
#include <fstream>
#include "../filereader.h"

TEST(FileReaderTest, FileIsOpen) {
    FileReader reader("test.txt");
    EXPECT_EQ(false, reader.FileIsOpen());
}

TEST(FileReaderTest, IsEmpty) {
    std::ofstream file("test.txt");
    file << "testing";
    file.close();

    FileReader reader("test.txt");
    reader.Open();
    reader.ReadLine();
    EXPECT_EQ(true, reader.IsEmpty());
}

TEST(FileReaderTest, ReadLine1) {
    std::ofstream file("test.txt");
    file << "testing";
    file.close();

    FileReader reader("test.txt");
    reader.Open();
    std::string line = reader.ReadLine();
    EXPECT_EQ(line, "testing");
}

TEST(FileReaderTest, ReadLine2) {
    std::ofstream file("test.txt");
    file.close();

    FileReader reader("test.txt");
    reader.Open();
    std::string line = reader.ReadLine();
    EXPECT_EQ(line, "");
}

#include <exception>
#include "filereader.h"

void FileReader::CheckExceptions() {
    if (!FileIsOpen()) {
        throw std::runtime_error("Failed to open file");
    }
}

FileReader::FileReader(std::string name) {
    file_name = name;
}

FileReader::~FileReader() {
    Close();
}

void FileReader::Open() {
    file_stream.open(file_name);
    CheckExceptions();
}

void FileReader::Close() {
    if (FileIsOpen()) {
        file_stream.close();
    }
}

bool FileReader::FileIsOpen() {
    return file_stream.is_open();
}

bool FileReader::IsEmpty() {
    return file_stream.eof();
}

std::string FileReader::ReadLine() {
    std::string new_line;
    std::getline(file_stream, new_line);
    return new_line;
}

#include <exception>
#include "filewriter.h"

void FileWriter::CheckExceptions() {
    if (!FileIsOpen()) {
        throw std::runtime_error("Failed to open file");
    }
}

FileWriter::FileWriter(std::string name) {
    file_name = name;
}

FileWriter::~FileWriter() {
    Close();
}

void FileWriter::Open() {
    file_stream.open(file_name);
    CheckExceptions();
}

void FileWriter::Close() {
    if (FileIsOpen()) {
        file_stream.close();
    }
}

bool FileWriter::FileIsOpen() {
    return file_stream.is_open();
}

void FileWriter::WriteLine(std::string line) {
    file_stream << line << "\n";
}

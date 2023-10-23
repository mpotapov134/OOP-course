#ifndef FILEREADER_H_INCLUDED
#define FILEREADER_H_INCLUDED

#include <string>
#include <fstream>

class FileReader {
    private:
        std::string file_name;
        std::ifstream file_stream;

        void CheckExceptions();

    public:
        FileReader(std::string name);

        ~FileReader();

        void Open();

        void Close();

        bool FileIsOpen();

        bool IsEmpty();

        std::string ReadLine();
};

#endif

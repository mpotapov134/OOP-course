#ifndef FILEWRITER_H_INCLUDED
#define FILEWRITER_H_INCLUDED

#include <string>
#include <fstream>

class FileWriter {
    private:
        std::string file_name;
        std::ofstream file_stream;

        void CheckExceptions();

    public:
        FileWriter(std::string name);

        ~FileWriter();

        void Open();

        void Close();

        bool FileIsOpen();

        void WriteLine(std::string line);
};

#endif

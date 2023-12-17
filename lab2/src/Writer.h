#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include <fstream>
#include <string>
#include "Universe.h"

/// @brief Class for saving Universe state to file.
class Writer {
    std::string m_file_name;
    std::ofstream m_file_stream;

    public:

    Writer() {}

    /**
     * @brief Construct a Writer for a Life 1.06 file and open the file.
     * @param file_name name of the output file.
     * @throw std::runtime_error if the file failed to open.
    */
    Writer(std::string file_name);
    ~Writer();

    /// @brief Check if the Writer has an open file.
    bool FileIsOpen();

    /**
     * @brief Open an output file.
     * @param file_name name of the output file.
     * @throw std::runtime_error if the file failed to open.
    */
    void Open(std::string file_name);

    /// @brief Close the associated file if there is one.
    void Close();

    /**
     * @brief Write the state of the universe to the associated file.
     * @param universe universe to be written.
     * @throw std::runtime_error if no file is open.
    */
    void Write(Universe& universe);
};

#endif

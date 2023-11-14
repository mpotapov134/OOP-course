#include <fstream>
#include <string>
#include <set>
#include <list>

#define POS_NOT_SPECIFIED -1

/// @brief Class for reading Life 1.06 files.
class Reader {
    private:
        std::string m_file_name;
        std::ifstream m_file_stream;
        std::ifstream::pos_type m_name_pos = POS_NOT_SPECIFIED;
        std::ifstream::pos_type m_rule_pos = POS_NOT_SPECIFIED;
        std::ifstream::pos_type m_coord_pos = POS_NOT_SPECIFIED;

        bool FormatIsCorrect();

        /// @brief Find the positions of the file's parts.
        void SetBlockPositions();

    public:
        Reader() {}

        /**
         * @brief Construct a Reader for a Life 1.06 file and open the file.
         * @param file_name name of the input file.
         * @throw std::runtime_error if the file failed to open or the format
         * of the file is not Life 1.06.
        */
        Reader(std::string file_name);
        ~Reader();

        /// @brief Check if the Reader has an open file.
        bool FileIsOpen();

        /**
         * @brief Open a Life 1.06 file.
         * @param file_name name of the input file.
         * @throw std::runtime_error if the file failed to open or the format
         * of the file is not Life 1.06.
        */
        void Open(std::string file_name);

        /// @brief Close the associated file.
        void Close();

        /**
         * @brief Read the name of the universe.
         * @return The name of the universe if it was specified.
         * @throw std::runtime_error if no name is specified.
        */
        std::string ReadName();

        /**
         * @brief Read the birth rule.
         * @return The set of birth rules specified in the file.
         * @throw std::runtime_error if no rule is specified.
         * std::invalid_argument if the rule is invalid.
        */
        std::set<int> ReadBirthRule();

        /**
         * @brief Read the survival rule.
         * @return The set of survival rules specified in the file.
         * @throw std::runtime_error if no rule is specified.
         * std::invalid_argument if the rule is invalid.
        */
        std::set<int> ReadSurvivalRule();

        /**
         * @brief Read the coordinates of alive cells.
         * @return Set of alive cells' coordinates.
         * @throw std::invalid_argument if the coordinates are invalid.
        */
        std::set<std::pair<int, int>> ReadCoords();
};

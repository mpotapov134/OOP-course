#include <fstream>
#include <string>
#include <set>
#include <list>

class Reader {
    private:
        std::string m_file_name;
        std::ifstream m_file_stream;
        std::ifstream::pos_type m_name_pos;
        std::ifstream::pos_type m_rule_pos;
        std::ifstream::pos_type m_coord_pos;

    public:
        Reader() {}
        Reader(std::string file_name);
        ~Reader();

        bool FileIsOpen();
        void Open(std::string file_name);
        void Close();
        bool FormatIsCorrect();
        void SetSeekPositions();

        std::string ReadName();
        std::set<int> ReadBirthRule();
        std::set<int> ReadSurvivalRule();
        std::list<std::pair<int, int>> ReadCoords();
};

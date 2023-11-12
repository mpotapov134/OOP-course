#include <stdexcept>
#include "Reader.h"

#define POS_NOT_SPECIFIED -1

// Removes redundant whitespaces from the beginning and the end of string.
std::string& Trim(std::string& str) {
    // Remove whitespace at the front
    str = str.substr(str.find_first_not_of(" \t"));
    // Remove whitespace at the end
    str = str.substr(0, str.find_last_not_of(" \t") + 1);
    return str;
}

bool Reader::FormatIsCorrect() {
    auto old_position = m_file_stream.tellg();
    m_file_stream.seekg(0);
    std::string line;
    std::getline(m_file_stream, line);
    m_file_stream.seekg(old_position);
    return line == "#Life 1.06";
}

void Reader::SetSeekPositions() {
    auto original_pos = m_file_stream.tellg();
    m_file_stream.seekg(0);

    m_file_stream.ignore(); // Ignore the first line
    auto line_pos = m_file_stream.tellg();

    std::string line;
    std::getline(m_file_stream, line);
    if (line.starts_with("#N")) {
        m_name_pos = line_pos;
    }
    else {
        m_name_pos = POS_NOT_SPECIFIED;
        m_file_stream.seekg(line_pos);
    }

    line_pos = m_file_stream.tellg();
    std::getline(m_file_stream, line);
    if (line.starts_with("#R")) {
        m_rule_pos = line_pos;
    }
    else {
        m_rule_pos = POS_NOT_SPECIFIED;
        m_file_stream.seekg(line_pos);
    }

    m_coord_pos = m_file_stream.tellg();

    m_file_stream.seekg(original_pos);
}

Reader::Reader(std::string file_name) {
    Open(file_name);
}

Reader::~Reader() {
    Close();
}

bool Reader::FileIsOpen() {
    return m_file_stream.is_open();
}

void Reader::Open(std::string file_name) {
    if (FileIsOpen()) {
        Close();
    }

    m_file_name = file_name;
    m_file_stream.open(file_name);
    if (!FileIsOpen()) {
        std::string err_msg = "Failed to open file \"" + file_name + "\".";
        throw std::runtime_error(err_msg);
    }

    if (!FormatIsCorrect) {
        std::string err_msg = "Invalid format of \"" + file_name + "\". The "
            "format should be Life 1.06.";
        throw std::runtime_error(err_msg);
    }

    SetSeekPositions();
}

void Reader::Close() {
    m_file_stream.close();
}

std::string Reader::ReadName() {
    if (m_name_pos == POS_NOT_SPECIFIED) {
        return "Unnamed";
    }

    m_file_stream.seekg(m_name_pos);
    std::string name;
    std::getline(m_file_stream, name);
    name = name.erase(0, 2); // Erase #N
    name = Trim(name); // Remove redundant whitespaces
    return name;
}

std::set<int> Reader::ReadBirthRule() {
    if (m_rule_pos == POS_NOT_SPECIFIED) {
        throw std::runtime_error("No birth rule specified");
    }

    m_file_stream.seekg(m_rule_pos);
    std::string rule;
    std::getline(m_file_stream, rule);

    rule.erase(rule.begin(), rule.begin() + rule.find('B'));
    rule.erase(rule.begin() + rule.find('/'), rule.end());
    if (rule.empty()) {
        throw std::runtime_error("No birth rule specified");
    }
    rule.erase(0, 1); // Erase 'B'

    std::set<int> birth_rule{};
    for (const auto& ch : rule) {
        int cells_number;
        std::string err_msg = "Invalid birth rule. The birth rule must be "
            "a sequence of digits in the range [0...8].";
        try {
            std::string character{ch};
            cells_number = std::stoi(character);
        } catch (std::invalid_argument) {
            throw std::invalid_argument(err_msg);
        }

        if (cells_number >= 9) {
            throw std::invalid_argument(err_msg);
        }

        birth_rule.insert(cells_number);
    }
    return birth_rule;
}

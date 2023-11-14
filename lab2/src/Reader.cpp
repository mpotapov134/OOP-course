#include <stdexcept>
#include "Reader.h"

// Removes redundant whitespaces from the beginning and the end of str.
std::string& Trim(std::string& str) {
    // Remove whitespace at the front
    str = str.substr(str.find_first_not_of(" \t"));
    // Remove whitespace at the end
    str = str.substr(0, str.find_last_not_of(" \t") + 1);
    return str;
}

// Simple char to int conversion
int ctoi(char ch) {
    return ch - '0';
}

// Check if str is a valid integer
bool IsInteger(std::string str) {
    int pos_in_str = 0;
    for (const auto& ch : str) {
        if (!std::isdigit(ch)) {
            if (!((ch == '-' || ch == '+') && pos_in_str == 0)) {
                return false;
            }
        }
        pos_in_str++;
    }
    return true;
}

bool Reader::FormatIsCorrect() {
    auto old_position = m_file_stream.tellg();
    m_file_stream.seekg(0);
    std::string line;
    std::getline(m_file_stream, line);
    m_file_stream.seekg(old_position);
    return line == "#Life 1.06";
}

void Reader::SetBlockPositions() {
    auto original_pos = m_file_stream.tellg();
    m_file_stream.seekg(0);
    m_file_stream.ignore(); // Ignore the first line containing the format

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
    SetBlockPositions();
}

void Reader::Close() {
    m_file_stream.close();
    m_name_pos = POS_NOT_SPECIFIED;
    m_rule_pos = POS_NOT_SPECIFIED;
    m_coord_pos = POS_NOT_SPECIFIED;
}

std::string Reader::ReadName() {
    if (m_name_pos == POS_NOT_SPECIFIED) {
        throw std::runtime_error("No name specified");
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

    auto pos_of_b = rule.find('B');
    if (pos_of_b == std::string::npos) { // Did not find
        throw std::runtime_error("No birth rule specified");
    }
    rule.erase(rule.begin(), rule.begin() + pos_of_b + 1);
    rule.erase(rule.begin() + rule.find('/'), rule.end());
    rule = Trim(rule);

    std::set<int> birth_rule{};
    for (const auto& ch : rule) {
        int cells_amount = ctoi(ch);
        if (cells_amount < 0 || cells_amount >= 9) {
            std::string err_msg = "Invalid birth rule. The birth rule must be "
                "a sequence of digits in the range [0...8].";
            throw std::invalid_argument(err_msg);
        }
        birth_rule.insert(cells_amount);
    }
    return birth_rule;
}

std::set<int> Reader::ReadSurvivalRule() {
    if (m_rule_pos == POS_NOT_SPECIFIED) {
        throw std::runtime_error("No survival rule specified");
    }
    m_file_stream.seekg(m_rule_pos);
    std::string rule;
    std::getline(m_file_stream, rule);

    auto pos_of_s = rule.find('S');
    if (pos_of_s == std::string::npos) { // Did not find
        throw std::runtime_error("No survival rule specified");
    }
    rule.erase(rule.begin(), rule.begin() + pos_of_s + 1);
    rule.erase(rule.begin() + rule.find('/'), rule.end());
    rule = Trim(rule);

    std::set<int> survival_rule{};
    for (const auto& ch : rule) {
        int cells_amount = ctoi(ch);
        if (cells_amount < 0 || cells_amount >= 9) {
            std::string err_msg = "Invalid survival rule. The survival rule "
                "must be a sequence of digits in the range [0...8].";
            throw std::invalid_argument(err_msg);
        }
        survival_rule.insert(cells_amount);
    }
    return survival_rule;
}

std::set<std::pair<int, int>> Reader::ReadCoords() {
    m_file_stream.seekg(m_coord_pos);
    std::set<std::pair<int, int>> coords;
    while (!m_file_stream.eof()) {
        std::string line;
        std::getline(m_file_stream, line);
        line = Trim(line); // Remove redundant whitespaces

        auto pos_of_space = line.find(' '); // x and y are separated by a space
        std::string x_str = line.substr(0, pos_of_space);
        std::string y_str = line.substr(pos_of_space + 1);

        if (!IsInteger(x_str) || !IsInteger(y_str)) {
            std::string err_msg = "Invalid coordinates. x and y coordinates "
                "of each cell must be integer values. Each alive cell must be "
                "on its own line, and the x and y coordinates are separated "
                "by a space.";
            throw std::invalid_argument(err_msg);
        }

        int x = std::stoi(x_str);
        int y = std::stoi(y_str);
        coords.insert(std::pair<int, int> {x, y});
    }
    return coords;
}

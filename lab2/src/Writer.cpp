#include "Writer.h"

Writer::Writer(std::string file_name) {
    Open(file_name);
}

Writer::~Writer() {
    Close();
}

bool Writer::FileIsOpen() {
    return m_file_stream.is_open();
}

void Writer::Open(std::string file_name) {
    if (FileIsOpen()) {
        Close();
    }

    m_file_name = file_name;
    m_file_stream.open(file_name);
    if (!FileIsOpen()) {
        std::string err_msg = "Failed to open file \"" + file_name + "\".";
        throw std::runtime_error(err_msg);
    }
}

void Writer::Close() {
    m_file_stream.close();
    m_file_name = "";
}

void Writer::Write(Universe& universe) {
    if (!FileIsOpen()) throw std::runtime_error("No output file.");
    m_file_stream << "#Life 1.06\n";
    m_file_stream << "#N " << universe.name() << "\n";

    m_file_stream << "#R B";
    for (auto rule : universe.birth_rule()) {
        m_file_stream << rule;
    }
    m_file_stream << "/S";
    for (auto rule : universe.survival_rule()) {
        m_file_stream << rule;
    }
    m_file_stream << "\n";

    for (const auto& x_y : universe.coords()) {
        m_file_stream << x_y.first << " " << x_y.second << "\n";
    }
}

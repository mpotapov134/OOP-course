#include <iostream>
#include "filereader.h"
#include "filewriter.h"
#include "parser.h"
#include "wordmap.h"

#define ERROR -1

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "2 arguments expected, " << (argc - 1) << " given\n";
        return ERROR;
    }

    FileReader reader(argv[1]);
    try {
        reader.Open();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << "\n";
        return ERROR;
    }

    Parser parser;
    WordMap word_map;
    while (!reader.IsEmpty()) {
        std::string line = reader.ReadLine();
        std::list<std::string> split_line = parser.Split(line);
        word_map.AddWords(split_line);
    }
    reader.Close();

    std::list<std::pair<std::string, int>> sorted_map = word_map.GetSortedData();

    FileWriter writer(argv[2]);
    try {
        writer.Open();
    } catch (std::runtime_error &exception) {
        std::cerr << exception.what() << "\n";
        return ERROR;
    }

    writer.WriteLine("Word,Quantity,Frequency");
    for (const auto &entry : sorted_map) {
        double frequency = (double) entry.second / word_map.TotalCount();
        std::string line = entry.first + "," + to_string(entry.second) + "," + \
            to_string(frequency);
        writer.WriteLine(line);
    }
    writer.Close();
}

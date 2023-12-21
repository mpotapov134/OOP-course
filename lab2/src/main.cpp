#include "Universe.h"
#include "CLHandler.h"
#include "CommandHandler.h"
#include "Reader.h"
#include "Writer.h"
#include <iostream>

void GetArgValues(int argc, char** argv, std::string& in, std::string& out,
        std::string& iter) {
    CommandLineHandler com_line(argc, argv);
    auto com_line_args = com_line.GetArgs();
    in = "";
    out = "";
    iter = "";

    for (const auto& arg : com_line_args) {
        if (arg.first == "-f") in = arg.second;
        else if (arg.first == "-o") out = arg.second;
        else if (arg.first == "-i") iter = arg.second;
    }
    if (in == "") in = "../game_files/default.lif";
}

void RunDefault(Universe& universe) {
    CommandHandler com_handler;
    while (true) {
        std::string command;
        std::getline(std::cin, command);
        std::pair<std::string, std::string> parsed_command;
        try {
            parsed_command = com_handler.ParseCommand(command);
        } catch(std::invalid_argument exc) {
            std::cerr << exc.what();
            continue;
        }

        int ret_code = com_handler.ExecuteCommand(parsed_command, universe);
        if (ret_code == EXIT) return;
    }
}

void RunSilent(Universe& universe, std::string output_file, int iter) {
    for (int i = 0; i < iter; i++) {
        universe.Tick();
    }

    Writer writer(output_file);
    writer.Write(universe);
}

int main(int argc, char** argv) {
    std::string input_file, output_file, iter;
    GetArgValues(argc, argv, input_file, output_file, iter);

    Reader reader(input_file);
    std::string name;
    std::set<int> b_rule, s_rule;
    std::set<std::pair<int, int>> coords;

    try {
        name = reader.ReadName();
    } catch (std::runtime_error) {
        name = Universe::default_name;
    }
    try {
        b_rule = reader.ReadBirthRule();
    } catch (std::runtime_error) {
        b_rule = Universe::default_b_rule;
    }
    catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }
    try {
        s_rule = reader.ReadSurvivalRule();
    } catch (std::runtime_error) {
        s_rule = Universe::default_s_rule;
    }
    catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }
    try {
        coords = reader.ReadCoords();
    } catch (std::invalid_argument exc) {
        std::cerr << exc.what();
        return -1;
    }

    Universe universe(name, b_rule, s_rule, coords);

    if (output_file == "") {
        universe.PrintUniverse();
        RunDefault(universe);
    }
    else {
        RunSilent(universe, output_file, std::stoi(iter));
    }
}

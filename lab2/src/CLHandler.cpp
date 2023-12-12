#include <stdexcept>
#include "CLHandler.h"

/// @brief Returns the short version of argument name.
static std::string GetShortName(std::string arg_name) {
    if (arg_name == "--iterations") return "-i";
    if (arg_name == "--file") return "-f";
    else return "-o";
}

/// @return true if num_of_iter represents a valid positive integer.
static bool IterIsValid(std::string num_of_iter) {
    for (const auto& ch : num_of_iter) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    if (std::stoi(num_of_iter) <= 0) return false;
    return true;
}



std::set<std::string> CommandLineHandler::valid_args{
    "-i", "--iterations", "-f", "--file", "-o", "--output"};


void CommandLineHandler::ParseArgs(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        std::string argument = argv[i];
        std::string short_name, value;
        std::string err_msg = "Argument \"" + argument + "\" is invalid.";

        if (argument.starts_with("--")) {
            auto pos_of_eq = argument.find('=');
            if (pos_of_eq == std::string::npos) {
                throw std::invalid_argument(err_msg);
            }

            std::string arg_name = argument.substr(0, pos_of_eq);
            if (!valid_args.contains(arg_name)) {
                throw std::invalid_argument(err_msg);
            }

            short_name = GetShortName(arg_name);
            value = argument.substr(pos_of_eq + 1);
        }

        else if (argument.starts_with("-")) {
            if (!valid_args.contains(argument)) {
                throw std::invalid_argument(err_msg);
            }
            short_name = argument;
            i++;
            value = (i < argc) ? argv[i] : "";
        }

        else throw std::invalid_argument(err_msg);

        if (arg_map.contains(short_name)) {
            throw std::invalid_argument("Invalid set of arguments.");
        }
        if (value.empty()) {
            throw std::invalid_argument("Value of argument not provided.");
        }
        if (short_name == "-i" && !IterIsValid(value)) {
            throw std::invalid_argument(
                "Number of iterations must be a positive integer.");
        }

        arg_map[short_name] = value;
    }
}

bool CommandLineHandler::SetOfArgsIsValid() {
    std::set<std::string> set_of_args{};
    for (auto const& value : arg_map) {
        set_of_args.insert(value.first);
    }
    std::set<std::string> no_args{};
    std::set<std::string> input_arg{"-f"};
    std::set<std::string> in_iter_out{"-f", "-i", "-o"};
    return (set_of_args == no_args || set_of_args == input_arg ||
        set_of_args == in_iter_out);
}

CommandLineHandler::CommandLineHandler(int argc, char** argv) {
    ParseArgs(argc, argv);
    if (!SetOfArgsIsValid()) {
        std::string err_msg = "Invalid set of arguments. Allowed sets are:\n"
            "No arguments;\nInput file name;\nInput file name, number of "
            "iterations, output file name.";
        throw std::invalid_argument(err_msg);
    }
}

std::map<std::string, std::string> CommandLineHandler::GetArgs() {
    return arg_map;
}

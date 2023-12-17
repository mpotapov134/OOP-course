#include "CommandHandler.h"

/// @return true if num_of_ticks represents a valid positive integer.
static bool TickIsValid(std::string num_of_ticks) {
    for (const auto& ch : num_of_ticks) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    if (std::stoi(num_of_ticks) <= 0) return false;
    return true;
}


std::set<std::string> CommandHandler::m_valid_commands {
    "dump", "tick", "t", "exit", "help"};

std::pair<std::string, std::string> CommandHandler::ParseCommand(
        std::string command) {
    std::string com_name, com_arg = "";
    auto space_pos = command.find(' ');
    if (space_pos == std::string::npos) {
        com_name = command;
    }
    else {
        com_name = command.substr(0, space_pos);
        com_arg = command.substr(space_pos + 1);
    }

    if (!m_valid_commands.contains(com_name)) {
        std::string err_msg = "Unknown command: " + com_name + ".";
        throw std::invalid_argument(err_msg);
    }

    if (com_name == "t") com_name = "tick";

    if (com_name == "tick") {
        if (com_arg == "") {
            com_arg = "1";
        }
        else if (!TickIsValid(com_arg)) {
            throw std::invalid_argument(
                "Number of ticks must be a positive integer.");
        }
    }

    if (com_name == "dump" && com_arg == "") {
        throw std::invalid_argument("No output file provided.");
    }

    return {com_name, com_arg};
}

void CommandHandler::ExecuteCommand(std::pair<std::string, std::string> command,
        Universe& universe) {

}

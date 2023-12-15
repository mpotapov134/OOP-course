#ifndef COMMAND_HANDLER_H_INCLUDED
#define COMMAND_HANDLER_H_INCLUDED

#include <string>
#include <set>
#include <utility>

/// @brief Class for handling game commands.
class CommandHandler {
    static std::set<std::string> valid_commands;

    public:

    /**
     * @brief Parses the command and splits it into name and value if possible.
     * @return pair of command name, command value. If the command has no value,
     * only the name is filled.
     * @exception std::invalid argument if either the command or its value is
     * invalid.
    */
    std::pair<std::string, std::string> ParseCommand(std::string command);
};

#endif

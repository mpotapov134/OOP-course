#ifndef COMMAND_HANDLER_H_INCLUDED
#define COMMAND_HANDLER_H_INCLUDED

#include <string>
#include <set>
#include <utility>
#include "Universe.h"

#define CONTINUE 0
#define EXIT 1

/// @brief Class for handling game commands.
class CommandHandler {
    static std::set<std::string> m_valid_commands;
    static std::string m_help_message;

    void Dump(std::string o_file, Universe& universe);
    void Tick(int num_of_ticks, Universe& universe);
    void Exit();
    void Help();

    public:

    /**
     * @brief Parses the command and splits it into name and value if possible.
     * @return pair of command name, command value. If the command has no value,
     * an empty string is written.
     * @exception std::invalid argument if either the command or its value is
     * invalid.
    */
    std::pair<std::string, std::string> ParseCommand(std::string command);

    /**
     * @brief Applies the given command to the universe.
     * @param command pair of command name, command value. It must be returned
     * by the ParseCommand method. Otherwise, the behavior is undefined.
     * @param universe the universe to refer to.
     * @return Either CONTINUE (in which case the game must go on) or EXIT
     * (the game must be finished).
    */
    int ExecuteCommand(std::pair<std::string, std::string> command, Universe& universe);
};

#endif

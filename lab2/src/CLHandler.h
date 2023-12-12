#ifndef CLHANDLER_H_INCLUDED
#define CLHANDLER_H_INCLUDED

#include <string>
#include <set>
#include <map>

/// @brief Class for reading and handling command line arguments.
class CommandLineHandler {
    static std::set<std::string> valid_args;
    std::map<std::string, std::string> arg_map;

    void ParseArgs(int argc, char** argv);
    bool SetOfArgsIsValid();

    public:

    /**
     * @brief Parses command line arguments, checks their validness and stores
     * their values.
     * @param argc number of arguments.
     * @param argv command line arguments.
     * @exception std::invalid_argument if the argument list is invalid.
    */
    CommandLineHandler(int argc, char** argv);

    /// @brief Returns map of command line arguments and their values.
    std::map<std::string, std::string> GetArgs();
};

#endif

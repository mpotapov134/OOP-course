#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <string>
#include <list>

class Parser {
    private:
        bool IsDelim(char character);

        void AddWord(std::list<std::string> &words, std::string &word);

    public:
        std::list<std::string> Split(std::string line);
};

#endif

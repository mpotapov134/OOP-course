#include "parser.h"

bool Parser::IsDelim(char character) {
    return !isalnum(character);
}

void Parser::AddWord(std::list<std::string> &words, std::string &word) {
    if (word != "") {
        words.insert(words.end(), word);
        word = "";
    }
}

std::list<std::string> Parser::Split(std::string line) {
    std::list<std::string> words;
    std::string word = "";

    for (auto character : line) {
        if (IsDelim(character)) {
            AddWord(words, word);
        }
        else {
            word += character;
        }
    }
    AddWord(words, word);

    return words;
}

#ifndef WORDMAP_H_INCLUDED
#define WORDMAP_H_INCLUDED

#include <string>
#include <map>
#include <list>
#include <utility>

using namespace std;

class WordMap {
    private:
        map<string, int> dictionary;
        int total_count = 0;

        static bool Compare(pair<string, int> &pair1, pair<string, int> &pair2);

    public:
        void AddWord(string word);

        void AddWords(list<string> words);

        map<string, int> &GetData();

        int TotalCount();

        list<pair<string, int>> GetSortedData();
};

#endif

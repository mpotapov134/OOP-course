#include "wordmap.h"

using namespace std;

bool WordMap::Compare(pair<string, int> &pair1, pair<string, int> &pair2) {
    return pair1.second > pair2.second || (pair1.second == pair2.second &&
        pair1.first < pair2.first);
}

void WordMap::AddWord(string word) {
    if (dictionary.count(word) > 0) {
        dictionary[word]++;
    }
    else {
        dictionary[word] = 1;
    }
    total_count++;
}

void WordMap::AddWords(list<string> words) {
    for (const auto &word : words) {
        AddWord(word);
    }
}

map<string, int> &WordMap::GetData() {
    return dictionary;
}

int WordMap::TotalCount() {
    return total_count;
}

list<pair<string, int>> WordMap::GetSortedData() {
    list<pair<string, int>> sorted_map(dictionary.begin(), dictionary.end());
    sorted_map.sort(Compare);
    return sorted_map;
}

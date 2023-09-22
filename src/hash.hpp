#ifndef HASH_HPP
#define HASH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class HashTable {
public:
    HashTable();
    void insertWord(string& word);
    void printOccurrences();
    void makeHeap();
    void makeBinaria();
    void makeAVL();
    void makeHuffman();
    bool stopwords(string& word);
    void separastopwords();
    int stringToKey(string& word);
    void printHeap();
    vector<string> pacote;
    vector<pair<string, int>> sortedWords;

private:
    unordered_map<string, int> table;
    string removeSpecialCharacters(string& word);
};

#endif // HASH_HPP

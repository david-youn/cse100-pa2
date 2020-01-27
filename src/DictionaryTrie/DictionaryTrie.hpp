/**
 * TODO: File Header
 *
 * Author:
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// template <char, unsigned int>
class TSTNode {
  private:
    char letter;
    unsigned int freq;

  public:
    TSTNode* left;
    TSTNode* right;
    TSTNode* middle;

    TSTNode(const char& c) : letter(c) {
        left = right = middle = nullptr;
        freq = 0;
    }

    void setFrequency(unsigned int f) { freq = f; }

    unsigned int getFrequency() { return freq; }

    char getChar() { return letter; }
};

/**
 * The class for a dictionary ADT, implemented as either
 * a mulit-way trie or a ternary search tree.
 */
class DictionaryTrie {
  private:
    // TODO: add private members and helper methods here
    TSTNode* root;

  public:
    /* TODO: add function header */
    DictionaryTrie();

    /* TODO: add function header */
    bool insert(string word, unsigned int freq);

    /* TODO: add function header */
    bool find(string word) const;

    /* TODO: add function header */
    vector<string> predictCompletions(string prefix,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    vector<string> predictUnderscores(string pattern,
                                      unsigned int numCompletions);

    /* TODO: add function header */
    ~DictionaryTrie();
};

#endif  // DICTIONARY_TRIE_HPP

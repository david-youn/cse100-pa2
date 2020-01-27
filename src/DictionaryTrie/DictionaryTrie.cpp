/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>

/* TODO */
DictionaryTrie::DictionaryTrie() { root = nullptr; }

/* TODO */
bool DictionaryTrie::insert(string word, unsigned int freq) {
    char ltr = word.at(0);
    int pos = 0;
    TSTNode* node = root;

    // word is empty
    if (word.length() == 0) {
        return false;
    }

    // if there is no root
    if (root == nullptr) {
        root = new TSTNode(ltr);
        node = root;
        for (int i = 1; i < word.length(); i++) {
            ltr = word.at(i);
            node->middle = new TSTNode(ltr);
            node = node->middle;
        }
        node->setFrequency(freq);

        return true;
    }

    // if there is a root and word is not empty
    while (true) {
        // left child
        if (ltr < node->getChar()) {
            if (node->left != nullptr) {
                node = node->left;
            } else {
                node->left = new TSTNode(ltr);
                node = node->left;

                for (int i = 1; i < word.length(); i++) {
                    ltr = word.at(i);
                    node->middle = new TSTNode(ltr);
                    node = node->middle;
                }
                node->setFrequency(freq);
                break;
            }
        }
        // right child
        else if (ltr > node->getChar()) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                node->right = new TSTNode(ltr);
                node = node->right;
                for (int i = 1; i < word.length(); i++) {
                    ltr = word.at(i);
                    node->middle = new TSTNode(ltr);
                    node = node->middle;
                }
                node->setFrequency(freq);
                break;
            }
        }
        // middle child
        else {
            // last letter of the word
            if (pos == word.length() - 1) {
                if (node->getFrequency() > 0) {
                    return false;
                }
                node->setFrequency(freq);
                return true;
            } else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    pos++;
                    ltr = word.at(pos);
                } else {
                    for (int i = pos + 1; i < word.length(); i++) {
                        ltr = word.at(i);
                        node->middle = new TSTNode(ltr);
                        node = node->middle;
                    }
                    node->setFrequency(freq);
                    break;
                }
            }
        }
    }
    return true;
}

/* TODO */
bool DictionaryTrie::find(string word) const {
    int pos = 0;

    // if TST is empty
    if (root == nullptr) {
        return false;
    }
    if (word.length() == 0) {
        return false;
    }
    TSTNode* node = root;
    char ltr = word.at(0);

    while (true) {
        // left child
        if (ltr < node->getChar()) {
            if (node->left != nullptr) {
                node = node->left;
            } else {
                return false;
            }
        }

        // right child
        else if (ltr > node->getChar()) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                return false;
            }
        }

        // middle child
        else {
            if (pos == word.length() - 1 && node->getFrequency() > 0) {
                return true;
            } else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    pos++;
                    if (pos == word.length()) {
                        return false;
                    }
                    ltr = word.at(pos);
                } else {
                    return false;
                }
            }
        }
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}
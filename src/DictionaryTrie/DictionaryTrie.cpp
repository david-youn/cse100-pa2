/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>

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
                pos++;
                for (int i = pos; i < word.length(); i++) {
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
                pos++;
                for (int i = pos; i < word.length(); i++) {
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
        TSTNode* tnode = node;
        cout << tnode->getChar() << endl;
        while (tnode->middle != nullptr) {
            tnode = tnode->middle;
            cout << tnode->getChar() << endl;
        }
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

// creating a struct for comparing pairs
/*
struct comPair {
    bool operator()(const pair<string, int>& lhs,
                    const pair<string, int>& rhs) {
        if (lhs.second == rhs.second) {
            return lhs.first > rhs.first;
        }
        return lhs.second > rhs.second;
    }
};
creating a priority queue of (string, int) pairs
typedef std::priority_queue<pair<string, int>, std::vector<pair<string, int>>,
                            comPair>
    my_queue;
*/

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    if (root == nullptr) {
        return {};
    }
    if (numCompletions == 0) {
        return {};
    }
    TSTNode* node = root;
    char ltr;
    vector<string> fvector;

    // traversing through every letter in prefix, should have node = the last
    // letter of prefix
    for (int i = 0; i < prefix.length(); i++) {
        ltr = prefix.at(i);
        // traversing through each node in that level to find a node with that
        // letter at that position in the prefix
        while (true) {
            // if we find the letter, node becomes the middle node
            if (ltr == node->getChar()) {
                // if the middle node exists, otherwise return empty vector
                if (node->middle != nullptr) {
                    node = node->middle;
                    break;
                } else if (i == prefix.length() - 1) {
                    if (node->getFrequency() > 0) {
                        // TODO: create a vector of size 1 with only this prefix
                        // in it and return unless numCompletions is 0
                        // return the vector
                        fvector.push_back(prefix);
                        return fvector;
                    }
                    return fvector;
                } else {
                    return fvector;
                }
            }
            // if letter is less than the nodes letter
            else if (ltr < node->getChar()) {
                // if the left node exists, otherwise return empty vector
                if (node->left != nullptr) {
                    node = node->left;
                } else {
                    return fvector;
                }
            } else {
                // if the right node exists, otherwise return empty vector
                if (node->right != nullptr) {
                    node = node->right;
                } else {
                    return fvector;
                }
            }
        }
    }
    // finding the node equal to the last letter of the prefix

    return fvector;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}
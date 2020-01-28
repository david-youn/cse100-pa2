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
    cout << "inserting: " << word << " with freq: " << freq << endl;
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
    cout << "last letter entered be: " << node->getChar() << endl;
    return true;
}

/* TODO */
bool DictionaryTrie::find(string word) const {
    cout << "finding: " << word << endl;
    int pos = 0;

    // if TST is empty
    if (root == nullptr) {
        cout << "root is null" << endl;
        return false;
    }
    if (word.length() == 0) {
        return false;
    }
    TSTNode* node = root;
    char ltr = word.at(0);
    cout << "first letter: " << ltr << endl;
    while (true) {
        cout << "printing whole word down the middle" << endl;

        TSTNode* tnode = node;
        cout << tnode->getChar() << endl;
        while (tnode->middle != nullptr) {
            tnode = tnode->middle;
            cout << tnode->getChar() << endl;
        }
        // left child
        if (ltr < node->getChar()) {
            cout << "ltr < node->getChar(): " << ltr << "<" << node->getChar()
                 << endl;
            if (node->left != nullptr) {
                node = node->left;
            } else {
                return false;
            }
        }
        // right child
        else if (ltr > node->getChar()) {
            cout << "ltr > node->getChar(): " << ltr << ">" << node->getChar()
                 << endl;
            if (node->right != nullptr) {
                node = node->right;
            } else {
                return false;
            }
        }
        // middle child
        else {
            cout << "ltr = node->getChar(): " << ltr << "=" << node->getChar()
                 << endl;
            if (pos == word.length() - 1 && node->getFrequency() > 0) {
                return true;
            } else {
                if (node->middle != nullptr) {
                    node = node->middle;
                    cout << "node = node->middle: " << node->getChar() << endl;
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
    std::vector<string> fvector(numCompletions);
    return {};
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}
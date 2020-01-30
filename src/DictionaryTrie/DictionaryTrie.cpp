/**
 * TODO: File Header
 *
 * Author:
 */
#include "DictionaryTrie.hpp"
#include <iostream>
#include <queue>

using namespace std;

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
struct comPair {
    bool operator()(pair<string, int>* w1, pair<string, int>* w2) {
        if (w1->second != w2->second) {
            return w1->second < w2->second;
        }
        return w1->first < w2->first;
    }
};
priority_queue<pair<string, int>*, vector<pair<string, int>*>, comPair> pq;
pair<string, int> pword;

static void ascendingInOrder(TSTNode* node, string str) {
    // base case:
    if (node->getFrequency() > 0) {
        pword = make_pair(str + node->getChar(), node->getFrequency());
        pq.push(&pword);
        cout << pword.first << ": " << pword.second << endl;
        if (node->left == nullptr && node->right == nullptr &&
            node->middle == nullptr) {
            str = str + node->getChar();
            return;
        }
    }
    if (node->left != nullptr) {
        ascendingInOrder(node->left, str);
    }
    if (node->right != nullptr) {
        ascendingInOrder(node->right, str);
    }
    if (node->middle != nullptr) {
        str = str + node->getChar();
        ascendingInOrder(node->middle, str);
    }
}

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

    // traversing through every letter in prefix except last, should have node =
    // the last letter of prefix
    for (int i = 0; i < prefix.length() - 1; i++) {
        ltr = prefix.at(i);

        // traversing through each node in that level to find a node with
        // that letter at that position in the prefix
        while (true) {
            // if we find the letter, node becomes the middle node
            if (ltr == node->getChar()) {
                // if the middle node exists, otherwise return empty vector
                if (node->middle != nullptr) {
                    node = node->middle;
                    break;
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

    /*
        ltr = prefix.at(prefix.length() - 1);
        // if prefix itself is a word
        if (node->getFrequency() > 0 && node->getChar() == ltr) {
            pword = make_pair(prefix, node->getFrequency());
            pq.push(&pword);
        }
    */
    // currently node points to the last letter of prefix, now need to traverse
    // all subtrees

    // the string that we will be "building" by going through the subtree
    prefix.pop_back();
    ascendingInOrder(node, prefix);
    // ascendingInOrder(root, "");

    // for after inserting all words in pq
    for (int i = 0; i < numCompletions; i++) {
        if (i >= pq.size()) {
            break;
        }
        pair<string, int>* temp = pq.top();
        fvector.push_back(temp->first);
        pq.pop();
    }

    cout << "vectortime" << endl;
    for (int i = 0; i < fvector.size(); i++) {
        cout << fvector.at(i) << endl;
    }
    return fvector;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    return {};
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {}
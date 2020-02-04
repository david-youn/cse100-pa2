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
        return w1->first > w2->first;
    }
};
struct rcomPair {
    bool operator()(pair<string, int>* w1, pair<string, int>* w2) {
        if (w1->second != w2->second) {
            return w1->second > w2->second;
        }
        return w1->first < w2->first;
    }
};

priority_queue<pair<string, int>*, vector<pair<string, int>*>, comPair> pq;
priority_queue<pair<string, int>*, vector<pair<string, int>*>, rcomPair> rpq;

pair<string, int> pword;

static void ascendingInOrder(TSTNode* node, string str,
                             unsigned int numCompletions, int minFreq) {
    // referenced algorithm from Stepik textbook
    // base case:
    int freq = node->getFrequency();
    if (freq > 0) {
        if (numCompletions > rpq.size()) {
            pair<string, int>* pword =
                new pair<string, int>(str + node->getChar(), freq);
            rpq.push(pword);
            if (freq < minFreq) {
                minFreq = freq;
            }
        } else if (freq > minFreq) {
            pair<string, int>* pword =
                new pair<string, int>(str + node->getChar(), freq);
            rpq.pop();
            rpq.push(pword);
        }
        if (node->left == nullptr && node->right == nullptr &&
            node->middle == nullptr) {
            str = str + node->getChar();
            return;
        }
    }
    if (node->left != nullptr) {
        ascendingInOrder(node->left, str, numCompletions, minFreq);
    }
    if (node->right != nullptr) {
        ascendingInOrder(node->right, str, numCompletions, minFreq);
    }
    if (node->middle != nullptr) {
        str = str + node->getChar();
        ascendingInOrder(node->middle, str, numCompletions, minFreq);
    }
}

/* TODO */
vector<string> DictionaryTrie::predictCompletions(string prefix,
                                                  unsigned int numCompletions) {
    int minFreq = 0;
    if (root == nullptr || numCompletions == 0 || prefix.length() == 0) {
        return {};
    }
    vector<string> fvector;
    TSTNode* node = root;
    char ltr;

    // traversing through every letter in prefix except last, should have node =
    // the last letter of prefix
    for (int i = 0; i < prefix.length(); i++) {
        ltr = prefix.at(i);

        // traversing through each node in that level to find a node with
        // that letter at that position in the prefix
        while (true) {
            // if we find the letter, node becomes the middle node
            if (ltr == node->getChar()) {
                if (i == prefix.length() - 1) {
                    break;
                }
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

    ltr = prefix.at(prefix.length() - 1);
    if (node->getChar() != ltr) {
        return fvector;
    }
    // if prefix itself is a word
    if (node->getFrequency() > 0) {
        pair<string, int>* pword =
            new pair<string, int>(prefix, node->getFrequency());
        pq.push(pword);
        minFreq = node->getFrequency();
    }

    // currently node points to the last letter of prefix, now need to traverse
    // all subtrees
    if (node->middle != nullptr) {
        ascendingInOrder(node->middle, prefix, numCompletions, minFreq);
    }

    while (rpq.size() != 0) {
        pq.push(rpq.top());
        rpq.pop();
    }
    for (int i = 0; i < numCompletions; i++) {
        if (pq.size() == 0) {
            break;
        }
        pair<string, int>* temp = pq.top();
        fvector.push_back(temp->first);
        delete (pq.top());
        pq.pop();
    }

    // emptying the rest of the priority queue
    while (pq.size() != 0) {
        delete (pq.top());
        pq.pop();
    }
    while (rpq.size() != 0) {
        delete (rpq.top());
        rpq.pop();
    }
    return fvector;
}

static void underscoreHelper(TSTNode* node, string finding, string str,
                             int pos) {
    if (pos >= finding.length()) {
        return;
    }

    // the letter at the position we need
    char curr = finding.at(pos);

    // go down all branches at that level
    // if (curr == '_') {
    if (node->left != nullptr) {
        underscoreHelper(node->left, finding, str, pos);
    }
    if (node->right != nullptr) {
        underscoreHelper(node->right, finding, str, pos);
    }
    //}
    if (node->getChar() == curr || curr == '_') {
        str = str + node->getChar();
        pos++;
        if (pos == finding.length()) {
            if (node->getFrequency() > 0) {
                pair<string, int>* pword =
                    new pair<string, int>(str, node->getFrequency());
                pq.push(pword);
            }
            return;
        } else if (node->middle != nullptr) {
            underscoreHelper(node->middle, finding, str, pos);
        }
    }
    return;
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    // emptying the priority queue before adding words to pq
    while (pq.size() != 0) {
        delete (pq.top());
        pq.pop();
    }
    vector<string> uvector;
    underscoreHelper(root, pattern, "", 0);
    // for after inserting all words in pq
    for (int i = 0; i < numCompletions; i++) {
        if (pq.size() == 0) {
            break;
        }
        pair<string, int>* temp = pq.top();
        uvector.push_back(temp->first);
        delete (pq.top());
        pq.pop();
    }
    // emptying the rest of the priority queue
    while (pq.size() != 0) {
        delete (pq.top());
        pq.pop();
    }
    return uvector;
}

static void deleteHelper(TSTNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        deleteHelper(node->left);
    }
    if (node->middle != nullptr) {
        deleteHelper(node->middle);
    }
    if (node->right != nullptr) {
        deleteHelper(node->right);
    }
    delete (node);
    node = nullptr;
}

/* TODO */
DictionaryTrie::~DictionaryTrie() {
    deleteHelper(root);
    root = nullptr;
    while (pq.size() != 0) {
        delete (pq.top());
        pq.pop();
    }
}
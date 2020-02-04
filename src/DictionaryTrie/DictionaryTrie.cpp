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
priority_queue<pair<string, int>*, vector<pair<string, int>*>, comPair> pq;
pair<string, int> pword;

static void ascendingInOrder(TSTNode* node, string str) {
    // referenced algorithm from Stepik textbook
    // base case:
    if (node->getFrequency() > 0) {
        pair<string, int>* pword =
            new pair<string, int>(str + node->getChar(), node->getFrequency());
        pq.push(pword);
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
    }

    // currently node points to the last letter of prefix, now need to traverse
    // all subtrees
    if (node->middle != nullptr) {
        ascendingInOrder(node->middle, prefix);
    }

    // for after inserting all words in pq
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
    return fvector;
}

static void underscoreHelper(TSTNode* node, string finding, string str,
                             int pos) {
    cout << "Pos: " << pos << endl;

    if (pos > finding.length()) {
        return;
    }
    if (pos < finding.length()) {
        cout << "looking for: " << finding.at(pos) << endl;
    }
    cout << "node->getChar(): " << node->getChar() << endl;
    cout << "str: " << str << endl;

    // the letter at the position we need
    char curr = finding.at(pos);

    // if we find it in the branch
    if (node->getChar() == curr) {
        // when at the length of the string
        if (pos == finding.length() - 1) {
            cout << "got em" << endl;
            cout << "node->getFrequency() at node->getChar(): "
                 << node->getChar() << ": " << node->getFrequency() << endl;
            // if we found a word that fits the underscores
            if (node->getFrequency() > 0) {
                cout << "found one" << endl;

                pair<string, int>* pword = new pair<string, int>(
                    str + node->getChar(), node->getFrequency());
                pq.push(pword);
            }
            return;
        } else if (node->middle != nullptr) {
            pos++;
            str = str + node->getChar();
            cout << "going mid" << endl;
            underscoreHelper(node->middle, finding, str, pos);
        }
    } else if (curr == '_') {
        if (pos == finding.length() - 1) {
            cout << "got em" << endl;
            cout << "node->getFrequency() at node->getChar(): "
                 << node->getChar() << ": " << node->getFrequency() << endl;
            // if we found a word that fits the underscores
            if (node->getFrequency() > 0) {
                cout << "found one" << endl;

                pair<string, int>* pword = new pair<string, int>(
                    str + node->getChar(), node->getFrequency());
                pq.push(pword);
            }
        } else if (node->middle != nullptr) {
            pos++;
            str = str + node->getChar();
            cout << "going mid" << endl;
            underscoreHelper(node->middle, finding, str, pos);
        }
        if (node->left != nullptr) {
            str = str + node->getChar();
            cout << "going left" << endl;
            underscoreHelper(node->left, finding, str, pos);
        }
        if (node->right != nullptr) {
            str = str + node->getChar();
            cout << "going right" << endl;
            underscoreHelper(node->right, finding, str, pos);
        }
    } else {
        return;
    }
}

/* TODO */
std::vector<string> DictionaryTrie::predictUnderscores(
    string pattern, unsigned int numCompletions) {
    // emptying the priority queue before adding words to pq
    while (pq.size() != 0) {
        delete (pq.top());
        pq.pop();
    }
    cout << "good to go" << endl;
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
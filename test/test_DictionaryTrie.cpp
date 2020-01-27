/**
 * TODO: File HEADER
 *
 * Author:
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "DictionaryTrie.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty test */
TEST(DictTrieTests, EMPTY_TEST) {
    DictionaryTrie dict;
    ASSERT_EQ(dict.find("abrakadabra"), false);
}

TEST(DictTrieTests, SET_GET_TEST) {
    TSTNode node('a');
    ASSERT_EQ(node.getFrequency(), 0);
    node.setFrequency(30);
    ASSERT_EQ(node.getFrequency(), 30);
}

TEST(DictTrieTests, LETTER_TEST) {
    TSTNode node('b');
    ASSERT_EQ(node.getChar(), 'b');
}

TEST(DictTrieTests, INSERT_TEST) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("word", 3));
    ASSERT_TRUE(dict.insert("test", 5));
    ASSERT_FALSE(dict.insert("word", 15));
    ASSERT_TRUE(dict.insert("wor", 2));
}

TEST(DictTrieTests, FIND_TEST) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("word", 3));
    ASSERT_TRUE(dict.insert("test", 5));
    ASSERT_FALSE(dict.insert("word", 15));
    ASSERT_TRUE(dict.insert("wor", 2));

    ASSERT_TRUE(dict.find("word"));
    ASSERT_FALSE(dict.find("wo"));
}

TEST(DictTrieTests, FIND_TEST2) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("word", 3));
    ASSERT_TRUE(dict.insert("wordo", 5));
    ASSERT_TRUE(dict.insert("test", 15));
    ASSERT_TRUE(dict.insert("abc", 2));
    ASSERT_TRUE(dict.find("abc"));
    ASSERT_FALSE(dict.find("bc"));
    ASSERT_TRUE(dict.find("wordo"));
}

/* TODO */

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
    ASSERT_FALSE(dict.find("yum"));
    ASSERT_TRUE(dict.find("wordo"));
}

TEST(DictTrieTests, FIND_TEST3) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("yum", 3));
    ASSERT_TRUE(dict.insert("yummy", 5));
    ASSERT_TRUE(dict.insert("yorek", 15));
    ASSERT_TRUE(dict.find("yorek"));
    ASSERT_TRUE(dict.find("yum"));
    ASSERT_TRUE(dict.find("yummy"));
}

TEST(DictTrieTests, FIND_TEST4) {
    DictionaryTrie dict;
    ASSERT_TRUE(dict.insert("garden", 3));
    ASSERT_TRUE(dict.insert("garage", 5));
    ASSERT_TRUE(dict.insert("garbage", 15));
    ASSERT_TRUE(dict.insert("tiger", 3));
    ASSERT_TRUE(dict.insert("tie", 5));
    ASSERT_TRUE(dict.insert("zebra", 15));
    ASSERT_TRUE(dict.insert("cat", 3));
    ASSERT_TRUE(dict.insert("car", 5));
    ASSERT_TRUE(dict.insert("art", 15));
    ASSERT_TRUE(dict.insert("eat", 3));
    ASSERT_TRUE(dict.insert("wow", 5));
    ASSERT_TRUE(dict.insert("b", 15));

    ASSERT_TRUE(dict.find("garden"));
    ASSERT_TRUE(dict.find("garage"));
    ASSERT_TRUE(dict.find("garbage"));
    ASSERT_TRUE(dict.find("tiger"));
    ASSERT_FALSE(dict.find("tig"));
    ASSERT_TRUE(dict.find("tie"));
    ASSERT_TRUE(dict.find("zebra"));
    ASSERT_TRUE(dict.find("cat"));
    ASSERT_TRUE(dict.find("car"));
    ASSERT_TRUE(dict.find("art"));
    ASSERT_TRUE(dict.find("eat"));
    ASSERT_TRUE(dict.find("wow"));
    ASSERT_TRUE(dict.find("b"));
    ASSERT_FALSE(dict.find("a"));
}
/* TODO */

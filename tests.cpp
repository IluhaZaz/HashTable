#include "hash_table.cpp"
#include <gtest/gtest.h>
#include <cstdio>

using namespace std;

TEST(HashTableTests, HashCheck) {
	UnorderedMap<int, int> h(15);
	EXPECT_EQ(3, h.get_hash(33));
}

TEST(HashTableTests, HashCheck2) {
	UnorderedMap<string, int> h(15);
	EXPECT_EQ(4, h.get_hash(string("abcd")));
}

TEST(HashTableTests, SearchCheck) {
	UnorderedMap<int, int> h(15);
	EXPECT_EQ(nullptr, h.search(5));
}
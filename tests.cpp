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

TEST(HashTableTests, MyPairCheck) {
	my_pair<int, int> p(2, 4);
	EXPECT_EQ(2, p.first);
	EXPECT_EQ(4, p.second);
}

TEST(HashTableTests, InsertCheck) {
	UnorderedMap<int, int> h(5);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.print();
}

TEST(HashTableTests, InsertCheck2) {
	UnorderedMap<int, int> h(10);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(9, 4);
	h.insert(14, 4);
	h.print();
}

TEST(HashTableTests, InsertCheck3) {
	UnorderedMap<int, int> h(4);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(9, 4);
	h.insert(14, 4);
	h.print();
}

TEST(HashTableTests, ContainsCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(9, 4);
	h.insert(14, 4);
	EXPECT_TRUE(h.contains(4));
	EXPECT_TRUE(h.contains(0));
	EXPECT_FALSE(h.contains(-4));
	EXPECT_FALSE(h.contains(13));
}
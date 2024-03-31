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

TEST(HashTableTests, SearchCheck2) {
	UnorderedMap<int, int> h(15);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(19, 4);
	h.erase(4);
	EXPECT_EQ(*h.search(19), 4);
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

TEST(HashTableTests, InsertOrAssignCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert_or_assign(4, 11);
	EXPECT_EQ(11, *h.search(4));
	h.insert_or_assign(-4, 51);
	EXPECT_EQ(51, *h.search(-4));
}

TEST(HashTableTests, EraseCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(14, -2);
	EXPECT_TRUE(h.erase(4));
	EXPECT_FALSE(h.search(4));
	EXPECT_FALSE(h.erase(72));
}

TEST(HashTableTests, CopyConstructorCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(2, 2);
	h.insert(0, 0);
	h.insert(4, 4);
	h.insert(14, -2);
	UnorderedMap<int, int> h2(h);
	h2.insert_or_assign(4, 6);
	EXPECT_EQ(4, *h.search(4));
	EXPECT_EQ(6, *h2.search(4));
}

TEST(HashTableTests, SwapCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(0, 0);
	h.insert(1, 1);
	h.insert(2, 2);

	UnorderedMap<int, int> h2(13);
	h2.insert(3, 3);
	h2.insert(4, 4);
	h2.insert(5, 5);
	h2.insert(6, 6);

	UnorderedMap<int, int> h3(h);

	UnorderedMap<int, int>::swap(h, h2);
	EXPECT_EQ(h3, h2);
}

TEST(HashTableTests, AssignOperatorCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(0, 0);
	h.insert(1, 1);
	h.insert(2, 2);
	h.insert(3, 3);

	UnorderedMap<int, int> h2 = h;
	EXPECT_EQ(h, h2);
}

TEST(HashTableTests, CountCheck) {
	UnorderedMap<int, int> h(27);
	h.insert(4, 11);
	h.insert(31, 11);
	h.insert(58, 11);
	h.insert(2, 1212);

	EXPECT_EQ(h.count(31), 3);
}

TEST(HashTableTests, ItemsCheck) {
	UnorderedMap<int, int> h(7);
	h.insert(4, 11);
	h.insert(31, 11);
	h.insert(58, 11);
	h.insert(2, 1212);
	auto v = h.items();
	for (const auto& val : v)
		cout << val.first << ": " << val.second << endl;
}
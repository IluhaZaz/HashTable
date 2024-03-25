#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <typeinfo>

using namespace std;

template<typename Key, typename Value>
class UnorderedMap {
private:
	vector<pair<Key, Value>> _data;
	size_t _size;
	size_t _used;
public:
	UnorderedMap(size_t size) :_data(size), _size(size), _used(0) {};

	size_t hash(const Key& k) {
		if (typeid(k) == typeid(string)) {
			stoi(k) % _size;
		}
		else {
			return k % _size;
		}
	}

	void clear() {
		_data.clear();
		_size = 0;
		used = 0;
	}

	~UnorderedMap() {
		this->clear();
	}

	void print() {
		for (const auto val&: _data) {
			cout << val.first() << " " << val.second << endl;
		}
	}

	void insert(Key key, Value value) {
		size_t = this->hash(key);
	}
};
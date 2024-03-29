#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <limits>


using namespace std;

template <typename F, typename S>
class my_pair : public pair<F, S> {
private:
	bool _is_initialized;
public:
	my_pair() {
		pair<F, S>();
		_is_initialized = false;
	}

	my_pair(F first, S second) {
		pair<F, S>(first, second);
		_is_initialized = false;
	}

	void set_initialized() {
		_is_initialized = true;
	}

	bool is_initialized() {
		return _is_initialized;
	}
};

template<typename Key, typename Value>
class UnorderedMap {
private:
	vector<my_pair<Key, Value>> _data;
	size_t _used;
public:
	UnorderedMap(): _data(20), _used(0) {}
	UnorderedMap(size_t size): _data(size), _used(0) {};

	size_t get_hash(const Key& k) {
		if constexpr (std::is_same_v<Key, int>) {
			return k % _data.size();
		}
		else if constexpr (std::is_same_v<Key, std::string>) {
			size_t sum = 0;
			for (auto val : k) {
				sum += int(val);
			}
			return sum % _data.size();
		}
	}

	void clear() {
		_data.clear();
		_used = 0;
	}

	~UnorderedMap() {
		this->clear();
	}

	void print() {
		for (const auto& val: _data) {
			cout << val.first << " " << val.second << endl;
		}
	}

	Value* search(Key key) {
		size_t hash = this->get_hash(key);
		if (!_data[hash].is_initialized()) {
			return nullptr;
		}
		for (int i = hash; i < _data.size(); i++) {
			if (!_data[i].is_initialized()) {
				return nullptr;
			}
			if (_data[i].first == key) {
				return &(_data[i].second);
			}
		}
			return nullptr;
	}

	void insert(Key key, Value value) {
		size_t = this->get_hash(key);
		
	}
};
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
	bool _deleted;
public:
	my_pair()
	: pair<F, S>() {
		_is_initialized = false;
		_deleted = false;
	}

	my_pair(F first, S second)
	: pair<F, S>(first, second) {
		_is_initialized = false;
		_deleted = false;
	}

	void set_initialized() {
		_is_initialized = true;
	}

	bool is_initialized() const {
		return _is_initialized;
	}

	bool is_deleted() const {
		return _deleted;
	}

	void del() {
		_is_initialized = false;
		_deleted = true;
	}
};

template<typename Key, typename Value>
class UnorderedMap {
private:
	vector<my_pair<Key, Value>> _data;
	size_t _used;
	float _coef;
public:
	UnorderedMap(): _data(20), _used(0), _coef(0.7) {}
	UnorderedMap(size_t size, float coef = 0.7): _data(size), _used(0), _coef(coef) {};

	size_t get_hash(const Key& k, size_t i = 0) {
		size_t size = _data.size();
		if constexpr (std::is_same_v<Key, int>) {
			return (k % size + i)%size;
		}
		else if constexpr (std::is_same_v<Key, std::string>) {
			size_t sum = 0;
			for (auto val : k) {
				sum += int(val);
			}
			return (sum % size + i)%size;
		}
	}

	void clear() {
		_data.clear();
		_used = 0;
	}

	UnorderedMap(const UnorderedMap& other) {
		_used = other._used;
		_coef = other._coef;
		_data = vector<my_pair<Key, Value>>(other._data);
	}

	~UnorderedMap() {
		this->clear();
	}

	void print() {
		for (const auto& val: _data) {
			if (val.is_initialized())
				cout << val.first << " " << val.second << endl;
		}
	}

	Value* search(Key key) {
		size_t hash = this->get_hash(key);
		size_t i = 0;
		while (_data[hash].is_initialized() || _data[hash].is_deleted()) {
			if (_data[hash].is_deleted()) {
				i++;
				hash = this->get_hash(key, i);
				continue;
			}
			if (_data[hash].first == key) {
				return &_data[hash].second;
			}
			i++;
			hash = this->get_hash(key, i);
		}
			return nullptr;
	}

	void remake() {
		vector<my_pair<Key, Value>> new_data((int)_data.size()*1.5);
		for (size_t i = 0; i < _data.size(); i++) {
			if (_data[i].is_initialized()) {
				size_t ind = this->get_hash(_data[i].first);
				size_t j = 0;
				while (new_data[ind].is_initialized()) {
					j++;
					ind = this->get_hash(_data[i].first, j);
				}
				new_data[ind] = _data[i];
			}
		}
		_data.clear();
		_data = new_data;
	}

	void insert(Key key, Value value) {
		if (search(key) != nullptr) {
			return;
		}
		size_t ind = this->get_hash(key);
		int i = 0;
		while (_data[ind].is_initialized()) {
			i++;
			ind = this->get_hash(key, i);
		}
		_data[ind] = my_pair<Key, Value>(key, value);
		_data[ind].set_initialized();
		_used++;
		if ((float)_used / _data.size() >= _coef) {
			this->remake();
		}
	}

	bool contains(Value value) {
		for (const auto& val : _data) {
			if(val.is_initialized())
			{
				if (val.second == value)
					return true;
			}
		}
		return false;
	}

	void insert_or_assign(Key key, Value value) {
		Value* old = this->search(key);
		if (old) {
			*old = value;
		}
		else {
			this->insert(key, value);
		}
	}

	bool erase(Key key) {
		if (!this->search(key)) {
			return false;
		}
		size_t ind = this->get_hash(key);
		int i = 0;
		while (_data[ind].first != key) {
			i++;
			ind = this->get_hash(key, i);
		}
		_data[ind].del();
		_used--;
	}

	static void swap(UnorderedMap& first, UnorderedMap& second) noexcept {
		
		std::swap(first._data, second._data);
		std::swap(first._used, second._used);
		std::swap(first._coef, second._coef);
	}

	bool operator==(const UnorderedMap& rhs) const {
		return _data == rhs._data && _coef == rhs._coef;
	}

	UnorderedMap& operator=(const UnorderedMap right) {
		swap(*this, right);
		return *this;
	}

	int count(Key key) {
		size_t hash = this->get_hash(key);
		size_t res = 0;
		for (const auto& val : _data) {

			if (val.is_initialized())
			{
				if (this->get_hash(val.first) == hash) {
					res++;
				}
			}
		}
		return res;
	}

	vector<pair<Key, Value>> items() {
		vector<pair<Key, Value>> v;
		for (const auto& p : _data) {
			v.push_back(pair<Key, Value>(p.first, p.second));
		}
		return v;
	}
};
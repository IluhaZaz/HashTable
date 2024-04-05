#include "hash_table.cpp"
#include <cstdio>
#include <random>
#include <vector>
#include <chrono>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine gen(seed);

int random(int low, int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

int main() {
	srand(time(0));
	size_t l = 20;
	vector<int> v(20);
	for (size_t i = 0; i < l; i++) {
		v[i] = random(0, 40);
	}

	UnorderedMap<int, int> d;

	for (const auto& val : v) {
		if (!d.search(val)) {
			d.insert(val, 1);
		}
		else {
			*d.search(val) += 1;
		}
	}

	size_t res = 0;
	for (const auto& val : d.items()) {
		if (val.second > 1) {
			res += val.second;
		}
	}
	d.print();
	cout << res;

}
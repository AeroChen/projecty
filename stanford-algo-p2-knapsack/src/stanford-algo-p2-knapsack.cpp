//============================================================================
// Name        : stanford-algo-p2-knapsack.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Knapsack solution
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <unordered_map>
using namespace std;

namespace std {

template<typename a, typename b>
struct hash<std::pair<a, b> > {
private:
	const hash<a> ah;
	const hash<b> bh;
public:
	hash() :
			ah(), bh() {
	}
	size_t operator()(const std::pair<a, b> &p) const {
		return ah(p.first) ^ bh(p.second);
	}
};

}

void readFileToVector(string filename, vector<pair<long, long> > &items,
		long &cap) {
	ifstream fs(filename);
	int num;
	fs >> cap;
	fs >> num;
	items.reserve(num);
	while (!fs.eof()) {
		int value, size;
		fs >> value;
		fs >> size;
		items.push_back(make_pair(value, size));
	}
	fs.close();
}

long getOptKnapackSub(int i, long capacity, vector<pair<long, long> > &items,
		unordered_map<pair<int, long>, long> &Asub) {
	// Base case
	if (i == 0)
		return 0;

	// Extract existing
	pair<int, long> key = make_pair(i, capacity);
	if (Asub.find(make_pair(i, capacity)) != Asub.end()) {
		return Asub[key];
	}

	// Calculate new
	pair<long, long> item = items[i - 1];
	if (capacity - item.second < 0) {
		Asub[key] = getOptKnapackSub(i - 1, capacity, items, Asub);
	} else {
		Asub[key] = max(getOptKnapackSub(i - 1, capacity, items, Asub),
				getOptKnapackSub(i - 1, capacity - item.second, items, Asub)
						+ item.first);
	}
	return Asub[key];
}

long getOptKnapsack(vector<pair<long, long> > &items, long capacity) {
	unordered_map<pair<int, long>, long> Asub;
	return getOptKnapackSub(items.size(), capacity, items, Asub);
}

int main() {
	vector<pair<long, long> > items;
	long capacity;
	readFileToVector("knapsack_big.txt", items, capacity);

	cout << "Knapsack opt:" << getOptKnapsack(items, capacity) << endl;

	return 0;
}

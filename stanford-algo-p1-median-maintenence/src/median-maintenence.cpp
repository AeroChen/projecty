//============================================================================
// Name        : median-maintenence.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : keep a running median for a stream of inputs
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <functional>
#include <numeric>
using namespace std;

vector<int> getRunningMedian(string filename) {
	vector<int> output_vec;
	fstream input_stream(filename);
	if (!input_stream.is_open()) {
		cout << "No file found" << endl;
		return output_vec;
	}

	priority_queue<int, vector<int>, greater<int>> min_heap;
	priority_queue<int> max_heap;

	int num;
	while (input_stream >> num) {
		// Add incoming number to heap
		if (max_heap.empty() || num < max_heap.top())
			max_heap.push(num);
		else
			min_heap.push(num);

		// Balance heap
		if (max_heap.size() > min_heap.size() + 1) {
			min_heap.push(max_heap.top());
			max_heap.pop();
		} else if (min_heap.size() > max_heap.size() + 1) {
			max_heap.push(min_heap.top());
			min_heap.pop();
		}

		// Get median
		int med =
				(max_heap.size() >= min_heap.size()) ?
						max_heap.top() : min_heap.top();
		output_vec.push_back(med);
	}
	return output_vec;
}

int main() {
	vector<int> vec = getRunningMedian("median.txt");
	cout << "Size of median vector: " << vec.size() << endl;
	cout << "Final output sum(vec)/10000: "
			<< accumulate(vec.begin(), vec.end(), 0) % 10000 << endl;
	return 0;
}

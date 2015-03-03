//============================================================================
// Name        : two-sum.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : two-sum for a fixed or a range of t
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
using namespace std;

unsigned long existTwoSumRange(vector<long long> &arr, long long tmin,
		long long tmax) {
	unordered_set<long long> t_set;

	// Sort input vector O(n log(n))
	sort(arr.begin(), arr.end());

	// Use two pointers to run through the list once O(n)
	unsigned long loptr = 0, hiptr = arr.size() - 1;
	while(loptr < hiptr) {
		long long x = arr[loptr];
		while(arr[hiptr] > tmax - x && loptr < hiptr) hiptr--;
		for (unsigned long i = hiptr; arr[i] >= tmin - x && loptr < hiptr; i--) {
			t_set.insert(x + arr[i]);
		}
		loptr++;
	}

	return t_set.size();
}

bool existTwoSum(vector<long long> &arr, long long t) {
	unordered_set<long long> hash_set;
	for (unsigned long i = 0; i < arr.size(); i++) {
		if (hash_set.find(t - arr[i]) != hash_set.end() && 2 * arr[i] != t) {
			return true;
		} else {
			hash_set.insert(arr[i]);
		}
	}
	return false;
}

void readFileToVector(string filename, vector<long long> &arr) {
	ifstream fs(filename);
	long long num;
	while (fs >> num) {
		arr.push_back(num);
	}
	fs.close();
	return;
}

int main() {
	vector<long long> input_vector;
	cout << "Reading input file ......" << endl;
	readFileToVector("2sum.txt", input_vector);
	cout << "Done!" << endl;

	// Convert to set and remove duplicate
	set<long long> s(input_vector.begin(), input_vector.end());
	input_vector.assign(s.begin(), s.end());

	unsigned long count = 0;
	count = existTwoSumRange(input_vector, -10000, 10000);
	cout << "Number of 2-sums exist: " << count << endl;

	return 0;
}

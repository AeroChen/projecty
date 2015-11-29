//============================================================================
// Name        : quicksort.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Quicksort
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> readFileToVector(const string filename) {
	ifstream input_file(filename.c_str());
	string curr_line;
	vector<int> vec;
	if(input_file.is_open()) {
		while ( getline(input_file, curr_line)){
			vec.push_back(atoi(curr_line.c_str()));
		}
	} else {
		cout<<"No file"<<endl;
	}

	return vec;
}

void printVectorNewLine(vector<int> vec) {
	for(int i = 0; i<vec.size(); i++){
		cout<<vec[i]<<endl;
	}
}

int quicksort(vector<int> &vec, int l, int r) {
	if (l>=r) {
		return 0;
	}
	int count = r-l;

	// Choose pivot
	int m = (r+l)/2;
	int p = m;
	if((vec[l] - vec[r]) * (vec[l] - vec[m]) <= 0) p = l;
	else if ( (vec[r] - vec[l]) * (vec[r] - vec[m]) <= 0) p = r;
	swap(vec[l],vec[p]);
	int pivot = vec[l];

	// Partition
	int i = l+1;
	for (int j = l+1; j <= r; ++j) {
		if(vec[j] < pivot) {
			swap(vec[j],vec[i++]);
		}
	}
	swap(vec[l],vec[i-1]);

	// Recursion
	count += quicksort(vec, l ,i-2 );
	count += quicksort(vec, i, r);
	return count;
}

int main() {
	vector<int> input_vec = readFileToVector("QuickSort.txt");
	int compare = quicksort(input_vec, 0 , input_vec.size()-1);
	printVectorNewLine(input_vec);
	cout<<"Comparision:"<<compare<<endl;
	return 0;
}

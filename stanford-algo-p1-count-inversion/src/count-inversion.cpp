//============================================================================
// Name        : count-inversion.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Count inversions in an array
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

unsigned countSplitInversion(vector<int> &vec, vector<int> left, vector<int> right) {
	int i = 0, j = 0, k = 0;
	unsigned count = 0;
	while(i<left.size() && j<right.size()) {
		if (left[i]<right[j]) {
			vec[k++] = left[i++];
		} else {
			count += left.size() - i;
			vec[k++] = right[j++];
		}
	}

	while(i<left.size()) {
		vec[k++] = left[i++];
	}

	while(j<right.size()) {
		vec[k++] = right[j++];
	}
	return count;
}

unsigned countInversion(vector<int> &vec) {
	if(vec.size() == 1) return 0;

	vector<int>::iterator middle = vec.begin() + vec.size()/2;
	vector<int> left_vec(vec.begin(),middle);
	vector<int> right_vec(middle,vec.end());
	unsigned left = countInversion(left_vec);
	unsigned right = countInversion(right_vec);
	unsigned split = countSplitInversion(vec,left_vec,right_vec);
	return left+right+split;
}

int main() {
	ifstream input_file("IntegerArray.txt");
	string curr_line;
	vector<int> input_vec;
	int n = 0;
	if (input_file.is_open()) {
		while ( getline(input_file, curr_line) ) {
			n++;
			input_vec.push_back(atoi(curr_line.c_str()));
			cout<<input_vec.back()<<endl;
		}
		input_file.close();
	} else {
		cout<<"No file"<<endl;
	}

	//vector<int> input = {1,3,5,2,4,6};
	cout<<countInversion(input_vec)<<endl;
	return 0;
}

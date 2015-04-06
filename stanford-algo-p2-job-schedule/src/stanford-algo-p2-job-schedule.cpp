//============================================================================
// Name        : stanford-algo-p2-job-schedule.cpp
// Author      : Xichen Shi
// Version     :
// Copyright   : 
// Description : Job scheduling with greedy algorithm
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

bool compareLengthDiff(pair<int,int> a, pair<int,int> b) {
	int da = a.first - a.second;
	int db = b.first - b.second;
	if(da > db) return true;
	else if (da == db) return (a.first > b.first);
	else return false;
}

bool compareRatio(pair<int,int> a, pair<int,int> b) {
	float ra = (float) a.first/a.second;
	float rb = (float) b.first/b.second;
	return (ra > rb);
}

void readFileToVector (string filename, vector<pair<int,int> > &job_vec) {
	ifstream fs(filename);
	int num;
	fs >> num;
	job_vec.reserve(num);
	while(!fs.eof()) {
		int weight, length;
		fs >> weight;
		fs >> length;
		job_vec.push_back(make_pair(weight, length));
	}
	fs.close();
}

long long sumWeightedCompletion(vector< pair<int,int> > &job_vec) {
	long long sum = 0;
	long long ci = 0;
	for(auto it = job_vec.begin(); it != job_vec.end(); it++) {
		ci += it->second; // completion time at i
		int wi = it->first; // weight at i
		sum += ci*wi;
	}
	return sum;
}

int main() {
	vector<pair<int,int> > job_vec;
	readFileToVector("jobs.txt", job_vec);

	// Use difference in weight and length for greedy score
	sort(job_vec.begin(),job_vec.end(), compareLengthDiff);
	cout<<sumWeightedCompletion(job_vec)<<endl;

	// Use ratio of weight and length for greedy score
	sort(job_vec.begin(),job_vec.end(), compareRatio);
	cout<<sumWeightedCompletion(job_vec)<<endl;
	return 0;
}

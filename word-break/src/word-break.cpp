//============================================================================
// Name        : word-break.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

template <class T>
void printVector(vector<T> v) {
	for(int i=0;i<v.size();i++) {
		cout<<v[i]<<",";
	}
	cout<<endl;
}

vector<string> wordBreak(string s, unordered_set<string> &dict) {
    unordered_map<int, vector<string> > dp;
    dp[s.length()] = vector<string>(1,"");

    for(int i=s.length()-1;i>=0;i--) {
    	vector<string> v;
        for(int j=s.length();i<j;j--) {
            string temp = s.substr(i,j-i);
            if(dp.find(j)!=dp.end() && dict.find(temp)!=dict.end()) {
                for(int k=0;k<dp[j].size();k++) {
                    v.push_back(temp+(dp[j][k].empty()?"":" ")+dp[j][k]);
                }
            }
        }
        if(!v.empty()) dp[i] = v;
    }
    return dp[0];
}

int main() {
	unordered_set<string> dict {"cat", "cats", "and", "sand", "dog"};
	string str = "catsanddog";
	vector<string> output = wordBreak(str,dict);
	for(int j=0;j<output.size();j++) {
		cout<< output[j]<<endl;
	}
	return 0;
}

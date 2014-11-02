//============================================================================
// Name        : combinations.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void generate(vector<vector<int> > &combination, vector<int> vec, int n, int k, int s)
{
    if(k==0){
        combination.push_back(vec);
        return;
    }
    for(int i=s; i<=n; i++){
        vector<int> temp(vec);
        temp.push_back(i);
        generate(combination, temp, n, k-1, i+1);
    }
}

vector<vector<int> > combine(int n, int k) {
    vector<vector<int> > outputs;
    vector<int> temp;
    generate(outputs,temp,n,k,1);
    return outputs;
}


int main() {
	vector<vector<int> > tests = combine(5,2);
	for(int i=0; i<tests.size();i++){
		for(int j=0;j<tests[i].size();j++) cout<< tests[i][j];
		cout<<endl;
	}
	return 0;
}

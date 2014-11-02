//============================================================================
// Name        : generate-parentheses.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void pushPars(vector<string> &vec, string str, int m, int n){
    if(m==0 && n==0){
        vec.push_back(str);
        return;
    }
    if(n>0) {
        pushPars(vec,str+"(",m+1,n-1);
    }
    if(m>0) {
        pushPars(vec,str+")",m-1,n);
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> output;
    pushPars(output,"",0,n);
    return output;
}

int main() {
	vector<string> tests = generateParenthesis(3);
	for(vector<string>::iterator it=tests.begin();it!=tests.end();it++){
		cout<< (*it) << endl;
	}
	return 0;
}

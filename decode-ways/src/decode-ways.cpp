//============================================================================
// Name        : decode-ways.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : decode-ways in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int numDecodings(string s) {
    if(s.empty()) return 0;
    int dp[2] = {1,0};
    dp[1] = (s[0] == '0')?0:1;
    for(int i=1;i<s.length();i++) {
    	int temp = ((s[i] == '0')?0:dp[1]) + ((atoi(s.substr(i-1,2).c_str()) <= 26 && s[i-1]!='0')?dp[0]:0);
        dp[0] = dp[1];
        dp[1] = temp;
    }
    return dp[1];
}

int main() {
	cout << numDecodings("123") << endl; // prints !!!Hello World!!!
	return 0;
}

//============================================================================
// Name        : reverse-polish-notation.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

int evalRPN(vector<string> &tokens) {
	stack<int> s;
	for(unsigned int i=0;i<tokens.size();++i)
	{
		if(tokens[i] == "+")
		{
			int v1 = s.top(); s.pop();
			int v2 = s.top(); s.pop();
			s.push(v2+v1);
		}
		else if (tokens[i] == "-")
		{
			int v1 = s.top(); s.pop();
			int v2 = s.top(); s.pop();
			s.push(v2-v1);
		}
		else if (tokens[i] == "*")
		{
			int v1 = s.top(); s.pop();
			int v2 = s.top(); s.pop();
			s.push(v2*v1);
		}
		else if (tokens[i] == "/")
		{
			int v1 = s.top(); s.pop();
			int v2 = s.top(); s.pop();
			s.push(v2/v1);
		}
		else
		{
			s.push(atoi(tokens[i].c_str()));
		}
	}
	return s.top();
}

int main() {
	vector<string> input_vec = {"2", "1", "+", "3", "*"};
	cout<<evalRPN(input_vec)<<endl;
	return 0;
}

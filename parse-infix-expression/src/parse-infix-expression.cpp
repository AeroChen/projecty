//============================================================================
// Name        : parse-infix-expression.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <utility>
#include <ctype.h>
using namespace std;

bool isOperator(char c) {
	if(c == '+' || c == '-' || c == '*' || c  == '/') return true;
	else return false;
}

float evalSimple(float a, float b, char op) {
	cout << a << op << b <<endl;
	if(op == '+') return a+b;
	else if (op == '-') return a-b;
	else if (op == '*') return a*b;
	else if (op == '/') return a/b;
	else return NULL;
}

bool isHigher(pair<char,int> op1, pair<char,int> op2) {
	if(op1.second > op2.second) return true;
	else if (op1.second < op2.second) return false;
	else if((op1.first == '+' || op1.first == '-')  && (op2.first == '*' || op2.first == '/')) return false;
	else return true;
}

float parseInfixExpression(string str) {
	stack<pair<char,int> > operators;
	stack<float> operands;
	int par_level = 0;
	int j=0;
	for(unsigned int i = 0; i<str.length();i++) {
		// Parentheses
		if(str[i] == '(') {
			par_level++;
			continue;
		} else if (str[i] == ')') {
			par_level--;
			continue;
		}

		// Digits
		if (isdigit(str[i]) && (i == 0 || !isdigit(str[i-1]))) j = i;
		if (isdigit(str[i]) && (i == str.length()-1 || !isdigit(str[i+1]))) {
			operands.push(float(atoi(str.substr(j,i-j+1).c_str())));
			continue;
		}

		// Operators
		if (isOperator(str[i])) {
			if(!operators.empty() && isHigher(operators.top(),make_pair(str[i],par_level))) {
				float a = operands.top(); operands.pop();
				float b = operands.top(); operands.pop();
				operands.push(evalSimple(b, a, operators.top().first));
				operators.pop();
			}
			operators.push(make_pair(str[i],par_level));
		}
	}

	while(!operators.empty()) {
		float a = operands.top(); operands.pop();
		float b = operands.top(); operands.pop();
		operands.push(evalSimple(b, a, operators.top().first));
		operators.pop();
	}
	return operands.top();
}

int main() {
	cout << parseInfixExpression("(1+2)*5*(6+(12/3)*10+1)") << endl; // prints !!!Hello World!!!
	return 0;
}

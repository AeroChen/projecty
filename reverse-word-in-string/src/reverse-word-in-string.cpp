//============================================================================
// Name        : reverse_word_in_string.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void reverseWords(string &s)
{
	stringstream ss(s);
	s.clear();
	string word;
	while(getline(ss, word, ' '))
	{
		if(word==""||word==" ") continue;
		word+=" ";
		s=word+s;
	}
	s=s.substr(0,s.length()-1);
}

int main() {
	string input_str = "one two three four";
	reverseWords(input_str);
	cout<<"\""<<input_str<<"\""<<endl;
	return 0;
}

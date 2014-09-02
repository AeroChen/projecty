//============================================================================
// Name        : count-and-say.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string countAndSay(int n);

int main() {
	countAndSay(11);
	return 0;
}

string countAndSay(int n) {
    if(n==1)
    {
        return("1");
    }
    string last_str = countAndSay(n-1);
    int count=0;
    char prev_char = 'a';
    string output_str = "";
    for(int i = 0; i < last_str.length(); i++)
    {
    	if(last_str[i]!=prev_char)
    	{
    		if (i!=0)
    		{
    			std::ostringstream os;
    			os<<count;
    			output_str += os.str() + prev_char;
			}
    		count=1;
    	}
    	else
    	{
    		count++;
    	}
    	prev_char = last_str[i];
    }
    std::ostringstream os;
	os<<count;
    output_str += os.str() + prev_char;
    cout<<n<<":"<<output_str<<endl;
    return output_str;
}

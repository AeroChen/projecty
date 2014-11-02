//============================================================================
// Name        : container-with-most-water.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxArea(vector<int> &height) {
    int p1 = 0;
    int p2 = height.size()-1;
    int area = 0;
    while(p1<p2)
    {
    	area = max(min(height[p1],height[p2])*(p2-p1),area);
        if(height[p1]<height[p2]) p1++;
        else p2--;
    }
    return area;
}

int main() {
	int heights[] = {1,3,4,2,5};
	vector<int> height(heights,heights+sizeof(heights)/sizeof(int));
	cout << maxArea(height) << endl; // prints !!!Hello World!!!
	return 0;
}

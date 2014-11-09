//============================================================================
// Name        : matrix-min-path-sum.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void printGrid(vector<vector<int> > &grid) {
	 for(unsigned int i = 0; i<grid.size(); i++) {
		   for(unsigned int j = 0; j<grid[i].size(); j++) {
			   cout<<grid[i][j]<<",";
		   }
		   cout<<endl;
	 }
}

int minPathSum(vector<vector<int> > &grid) {
   for(unsigned int i = 0; i<grid.size(); i++) {
	   for(unsigned int j = 0; j<grid[i].size(); j++) {
		   if(i!=0 && j!=0) {
			   grid[i][j] += min(grid[i-1][j],grid[i][j-1]);
		   } else if (i==0 && j!=0) {
			   grid[i][j] += grid[i][j-1];
		   } else if (j==0 && i!=0) {
			   grid[i][j] += grid[i-1][j];
		   }
	   }
   }
   return grid.back().back();
}

int main() {
	vector<vector<int> >  test = {
			{1,2,3,4,5},
			{2,3,8,3,1},
			{3,2,5,4,3},
			{4,4,7,7,3},
			{5,7,9,0,9}
	};
	printGrid(test);
	cout << "Min-sum is: "<<minPathSum(test) << endl; // prints !!!Hello World!!!
	return 0;
}

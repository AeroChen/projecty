//============================================================================
// Name        : search-sorted-2d-matrix.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Search sorted 2d matrix in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int> > &matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    int l = 0, r = m*n-1;
    while(l<=r) {
        int mid = (l+r)/2;
        cout<<mid<<endl;
        if(matrix[mid/n][mid%n] == target) return true;
        else if (matrix[mid/n][mid%n] < target) l = mid+1;
        else r = mid-1;
    }
    return false;
}

int main() {
	vector<vector<int> > matrix = {
			{1,2,3},
			{4,5,6},
			{7,8,9}
	};
	cout << searchMatrix(matrix,9) << endl; // prints !!!Hello World!!!
	return 0;
}

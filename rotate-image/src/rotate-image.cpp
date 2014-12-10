//============================================================================
// Name        : rotate-image.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : rotate-image in C++, Ansi-style
//               You are given an n x n 2D matrix representing an image.
//               Rotate the image by 90 degrees (clockwise).
//               Could you do this in-place?
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

void rotate(vector<vector<int> > &matrix) {
    int n = matrix.size();
    for(int i=0; i<n/2; i++) {
        int m = n-2*i;
        for(int j=0; j< m-1;j++) {
            int temp = matrix[i+j][i];
            matrix[i+j][i] = matrix[i+m-1][i+j];
            matrix[i+m-1][i+j] = matrix[i+m-j-1][i+m-1];
            matrix[i+m-j-1][i+m-1] = matrix[i][i+m-j-1];
            matrix[i][i+m-j-1] = temp;
        }
    }
}

void printMatrix(vector<vector<int>> matrix) {
	for(int i = 0; i<matrix.size(); i++){
		for(int j = 0; j<matrix[i].size(); j++) {
			cout<<matrix[i][j];
			if(j!=matrix[i].size()-1) cout<<",";
		}
		cout<<";"<<endl;
	}
}

int main() {
	vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
	cout<<"Original Matrix:"<<endl;
	printMatrix(matrix);
	rotate(matrix);
	cout<<"Rotated Matrix:"<<endl;
	printMatrix(matrix);
	return 0;
}

//============================================================================
// Name        : max-product-subarray.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Max product in interger subarray in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int maxProduct(int A[], int n) {
    if(n==0) return 0;
    int output = A[0];
    int maxhere = A[0];
    int minhere = A[0];

    for(int i=1;i<n;i++){
        if(A[i]<0) swap(maxhere,minhere);
        maxhere = max(maxhere*A[i],A[i]);
        minhere = min(minhere*A[i],A[i]);
        output = max(maxhere,output);
    }

    return output;
}

int main() {
	int test[] = {1,3,5,-9,-7,2,3,4,6,-10};
	cout << maxProduct(test, sizeof(test)/sizeof(int)) << endl; // prints !!!Hello World!!!
	return 0;
}

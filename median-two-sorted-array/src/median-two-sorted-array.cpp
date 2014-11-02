//============================================================================
// Name        : median-two-sorted-array.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
using namespace std;

double searchMedian(int A[], int B[], int m, int n, int l, int r)
{
	if(l>r) return searchMedian(B,A,n,m,max(0,(n-m)/2),min(n-1,(n+m)/2));
    int i = (l+r)/2;
    int j = (m+n)/2 - i;
    if( j>0 && A[i] < B[j-1])
    {
    	return searchMedian(A,B,m,n,i+1,r);
    }
    else if( j<n && A[i] > B[j])
    {
    	return searchMedian(A,B,m,n,l,i-1);
    }
    else
    {
    	if((m+n)%2 == 1) return  A[i]; // odd case
    	else if(j==0) return (A[i] + A[i-1])/2.0; // even cases
    	else if(i==0) return (A[i] + B[j-1])/2.0;
    	else return (A[i] + max(A[i-1],B[j-1]))/2.0;
    }
}


double findMedianSortedArrays(int A[], int m, int B[], int n) {
	if(m>n) return searchMedian(A,B,m,n,max(0,(m-n)/2),min(n-1,(n+m)/2));
	else return searchMedian(B,A,n,m,max(0,(n-m)/2),min(n-1,(n+m)/2));
}

int main() {
	int A[2] = {1,2};
	int B[2] = {1,2};
	int m = sizeof(A)/sizeof(A[0]);
	int n = sizeof(B)/sizeof(B[0]);
	cout<<findMedianSortedArrays(A,m,B,n)<<endl;
}

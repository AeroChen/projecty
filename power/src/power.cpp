/*
 * power.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: AeroChen
 */

#include <iostream>
using namespace std;

double pow(double x, int n) {
	if(n==0) return 1;
	double temp = pow(x,n/2);
	if(n%2 == 0) return temp*temp;
	else if(n>0) return temp*temp*x;
	else return temp*temp/x;
}

int main() {
	double x = 1.2;
	int n = 4;
	cout<<x<<"^"<<n<<"="<<pow(x,n)<<endl;
	return 0;
}



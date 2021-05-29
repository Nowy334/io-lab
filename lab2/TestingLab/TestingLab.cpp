// TestingLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include "Matrix.h"
using namespace std;

double initializer(int i, int j)
{
	return 2 * i - j / 2.0;
}

int main()
{
	//Matrix A(2, vector<double>({ 0., 1., 3., 2. }));
	Matrix A(0, 0.);
	Matrix B(3, 1.);
	A = A * B;
	A.print();
	cout << A.rows << "\t" << A.columns << endl;
}

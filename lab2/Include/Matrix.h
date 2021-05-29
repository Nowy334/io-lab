#pragma once
#ifdef MATRIXLIB_EXPORTS
#define MATRIXLIB_API __declspec(dllexport)
#else
#define MATRIXLIB_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

class MATRIXLIB_API Matrix
{
private:
	int at(int i, int j);
	void _swap(Matrix &mat, int row1, int row2, int col);
	void _set_shape(int rows, int columns);
	double _determinant(Matrix matrix, int n);
public:

	vector<double> data;
	int rows;
	int columns;

	//Copy constructor
	Matrix(const Matrix &original);

	//Constructor initializing square matrix with zeros and each dimension equal to 'shape' (shape x shape).
	Matrix(int shape, double initializer = 0.0);

	/*initializer_func represents a function taking two arguments corresponding
	to rows and columns iterators. Lambda expressions are allowed.
	*/
	Matrix(int shape, double(*initializer_func)(int, int)); 

	//Constructor initializing square matrix with values of a given vector.
	Matrix(int shape, vector<double> data);

	//The same constructors but creating matrices with shape rows x columns
	Matrix(int rows, int columns, double(*initializer_func)(int, int));
	Matrix(int rows, int columns, double initializer = 0.);
	Matrix(int rows, int columns, vector<double> data);

	~Matrix();

	//Loads data from two dimensional array. Returns False in case of error.
	bool load_data(double** data);

	//Loads data of specified shape from one dimensional vector. Returns False in case of error.
	bool load_data(vector<double> data, int rows, int columns);

	//Loads data using passed function taking two int arguments representing rows and columns
	//indexes of a specific element. Returns False in case of error.
	bool load_data(double(*initializer_func)(int, int));

	// Prints elements of the matrix. Use only in TestingLab.
	void print();

	// Returns an element at specific location of a matrix,
	// Converts rows and columns indexes so the element of one dimensional vector can be properly read.
	// !!! NO NEED TO TEST AS IT WORKS PROPERLY !!!
	double & operator () (int rows, int columns);

	// Returns result of multiplication operation between two matrices.
	Matrix operator * (Matrix B);

	// Returns result of multiplication by integer value.
	Matrix operator * (int multiplier);

	// Returns result of addition of two matrices.
	Matrix operator + (Matrix B);

	// Checks if the matrices contain the same values and have the same shape.
	// !!! NO NEED TO TEST AS IT WORKS PROPERLY !!!
	bool operator == (Matrix B);

	// Returns rank of the matrix.
	int rank();

	// Returns determinant of the matrix.
	double determinant();
};

class InvalidShapeDeterminant : public exception
{
public:
	virtual const char* what() const throw();
};


#include "pch.h"

TEST(Rank, CheckRankInitializerFunc) {
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) {return (double)i; });
	ASSERT_EQ(A.rank(), 1);
}

TEST(constructor, CheckCopyConstructor) {
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) {return (double)i; });
	Matrix B(A);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			EXPECT_EQ(A(i,j), B(i,j)) <<"Nie zgadza sie";
		}
	}
}

TEST(constructor, CheckShapeConstructor) {
	int shape = 8;
	Matrix A(shape);
	for (int i = 0; i < shape; i++) {
		for (int j = 0; j < shape; j++) {
			EXPECT_EQ(A(i, j), 0.0) << "Nie ma wartosci 0.0";
		}
	}
	EXPECT_EQ(A.rows, shape) << "Nie ma odpowiedniej ilosc rzedow";
	EXPECT_EQ(A.columns, shape) << "Nie ma odpowiedniej ilosci kolumn";
}

TEST(constructor, CheckShapeLambdaConstructor) {
	int shape = 8;
	Matrix A(shape, [](int i, int j) {return (double)i; });
	for (int i = 0; i < shape; i++) {
		for (int j = 0; j < shape; j++) {
			EXPECT_EQ(A(i, j), i) << "Nie zgadzaja sie wartosci";
		}
	}
}

TEST(constructor, CheckVectorConstructor) {
	int shape = 2;
	int x = 0;
	vector<double> v1 = {1,2,3,4};
	Matrix A(shape, v1);
	for (int i = 0; i < shape; i++) {
		for (int j = 0; j < shape; j++) {
			EXPECT_EQ(A(i, j), v1[x]) << "Nie zgadzaja sie wartosci";
			x++;
		}
	}
}

TEST(constructor, CheckRowsAndColumnsLambdaConstructor) {
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) {return (double)i; });
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			EXPECT_EQ(A(i, j), i) << "Nie zgadzaja sie wartosci";
		}
	}
}

TEST(constructor, CheckRowsAndColumnsVectorConstructor) {
	vector<double> v1 = { 1,2,3,4 };
	int x = 0;
	Matrix A(2,2, v1);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(A(i, j), v1[x]) << "Nie zgadzaja sie wartosci";
			x++;
		}
	}
}

class MultiplicationBetweenTwoMatricesTests : public ::testing::TestWithParam<tuple<Matrix, Matrix, Matrix>> {};

TEST_P(MultiplicationBetweenTwoMatricesTests, MultiplicationBetweenTwoMatrices)
{
	Matrix A = get<0>(GetParam());
	Matrix B = get<1>(GetParam());
	Matrix expected_result = get<2>(GetParam());
	A = A * B;
	EXPECT_TRUE(A == expected_result) << "Operator mnozenia nie dziala";
}

INSTANTIATE_TEST_CASE_P(MultiplicationBetweenTwoMatricesTests, MultiplicationBetweenTwoMatricesTests,
	::testing::Values(
		make_tuple(Matrix(2, 3.2), Matrix(2, 3.2), Matrix(2, 8.4)),
		make_tuple(Matrix(2, 2.0), Matrix(2, 2.0), Matrix(2, 8.0)),
		make_tuple(Matrix(3, 2, 2.0), Matrix(2, 3, 3.0), Matrix(3, 3, 12.0)),
		make_tuple(Matrix(2, 2.0), Matrix(2, 3, 3.0), Matrix(2, 3, 12.0)),
		make_tuple(Matrix(2, 2), Matrix(2, 2), Matrix(2, 8)),
		make_tuple(Matrix(2, 2.5), Matrix(2, 2), Matrix(2, 15))
	));



class AdditionMatrixTests : public ::testing::TestWithParam<tuple<Matrix,Matrix>> {};

TEST_P(AdditionMatrixTests, CheckAddition)
{
	Matrix A = get<0>(GetParam());
	Matrix expected_result = get<1>(GetParam());
	A = A + A;
	EXPECT_TRUE(A == expected_result) << "Dodawanie nie dzia³a";
}

INSTANTIATE_TEST_CASE_P(AdditionMatrixTest, AdditionMatrixTests,
	::testing::Values(
		make_tuple(Matrix(2, 1.0), Matrix(2, 2.0)),
		make_tuple(Matrix(2, 2.2), Matrix(2, 4.4)),
		make_tuple(Matrix(2, -2.2), Matrix(2, -4.4))));



TEST(LoadDataTests, CheckLoadDataTest) {
	int rows = 2;
	int columns = 2;

	double** arr = new double* [rows];
	for (int i = 0; i < rows; ++i)
		arr[i] = new double[columns];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			arr[i][j] = 2;
		}
	}

	Matrix A(columns, rows);
	ASSERT_TRUE(A.load_data(arr) == true) << "Nieprawid³owe wartoœci";
}

TEST(LoadDataTests, CheckLoadDataVectorTest) {
	vector<double> v = { 4,3,2,1 };
	Matrix A(2);
	Matrix B(2, v);

	ASSERT_TRUE(A.load_data(v, 2, 2) == true) << "Zaladowanie nie dziala";
	ASSERT_TRUE(A == B) << "Nieprawid³owe wartoœci";
	
}

TEST(LoadDataTests, CheckLoadDataLambdaTest) {
	Matrix A(2);
	EXPECT_TRUE((A.load_data([](int i, int j) {return (double)2; })) == true) <<"Za³adowanie nie dzia³a";
	
}


class DeterminantMatrixTests : public ::testing::TestWithParam<tuple<Matrix, double>> {};

TEST_P(DeterminantMatrixTests, CheckAddition)
{
	Matrix A = get<0>(GetParam());
	double expected_result = get<1>(GetParam());
	EXPECT_TRUE(A.determinant() == expected_result) << "Nieprawid³owa determinanta" << "\nDeterminanta obliczona: " << A.determinant() << "\nDeterminanta zadana: " << expected_result;
}

INSTANTIATE_TEST_CASE_P(DeterminantMatrixTest, DeterminantMatrixTests,
	::testing::Values(
		make_tuple(Matrix(2, 1.0), 0),
		make_tuple(Matrix(2, 2), 0),
		make_tuple(Matrix(2, 2.2), 0),
		make_tuple(Matrix(2, {1,2,3,4}), -2),
		make_tuple(Matrix(2, {1.1, 2.1, 3.1, 4.1}), -2.0)
	
	));



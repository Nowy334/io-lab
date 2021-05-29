#include "pch.h"

class MultiplicationByIntTests : public ::testing::TestWithParam<tuple<Matrix, int, Matrix>> {

};
TEST_P(MultiplicationByIntTests, CheckMultiplication)
{
	Matrix A = get<0>(GetParam());
	int multiplier = get<1>(GetParam());
	Matrix expected_result = get<2>(GetParam());
	A = A * multiplier;
	ASSERT_TRUE(A == expected_result) << "multiplier: " << multiplier;
}

INSTANTIATE_TEST_CASE_P(MultiplicationByIntTest, MultiplicationByIntTests,
	::testing::Values(
		make_tuple(Matrix(2, 1.0), 2, Matrix(2, 2.0)),
		make_tuple(Matrix(5,3, 1.0), 2, Matrix(5,3, 2.0)),
		make_tuple(Matrix(5, 1.0), 10, Matrix(5, 10.0)),
		make_tuple(Matrix(5, 1.0), 0, Matrix(5, 0.0)),
		make_tuple(Matrix(5, 1.0), -1, Matrix(5, -1.0)),
		make_tuple(Matrix(2, 1.0), 4, Matrix(2, 4.0)),
		make_tuple(Matrix(2, 2.0), 2, Matrix(2, 4.0)),
		make_tuple(Matrix(2, 3.0), 2, Matrix(2, 6.0))));
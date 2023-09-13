#pragma once

#define _USE_MATH_DEFINES

#include <string>
#include <stdexcept>
#include <math.h>

// A matrix class that can be used for CPU operations, such as object
// transformation and CPU device rendering.  Cannot be used on GPU, except for
// copying the numerical data over.
class Matrix
{
public:
	Matrix();
	Matrix(int _rows, int _columns);
	Matrix(float* _values, int _rows, int _columns);
	Matrix(const Matrix& mat);
	~Matrix();

	// Non-Static Methods
	Matrix Copy();
	void Copy(float* output_location);
	bool Equals(Matrix mat);
	int GetRows();
	int GetColumns();
	//TODO: Write Function for Determinant based on LU Decomposition.
	float GetValue(int row, int column);
	std::string ToString();

	// Static Methods
	static Matrix GetTranslationMatrix(float x, float y, float z);
	static Matrix GetRotationMatrix(float x, float y, float z);
	static Matrix GetScaleMatrix(float x, float y, float z);

	// Operators
	Matrix& operator=(const Matrix& mat);
	Matrix operator+(Matrix mat);
	Matrix operator-(Matrix mat);
	Matrix operator*(Matrix mat);

	// Static Operator Equivalents for use in Arrays
	static void Add(float* mat1, int mat1_rows, int mat1_columns,
		            float* mat2, int mat2_rows, int mat2_columns,
		            float* output_location);
	static void Subtract(float* mat1, int mat1_rows, int mat1_columns,
					     float* mat2, int mat2_rows, int mat2_columns,
					     float* output_location);
	static void Multiply(float* mat1, int mat1_rows, int mat1_columns,
					     float* mat2, int mat2_rows, int mat2_columns,
					     float* output_location);

protected:
	float* values;
	int rows, columns;

private:
	static void FillZeroArray(float* array, int rows, int columns);
	void InitializeArray(float* _values = nullptr);
};
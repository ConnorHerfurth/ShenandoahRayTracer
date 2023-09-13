#include "Matrix.h"

Matrix::Matrix()
{
	rows = 1;
	columns = 1;

	InitializeArray();
}

Matrix::Matrix(int _rows, int _columns)
{
	rows = _rows;
	columns = _columns;

	InitializeArray();
}

Matrix::Matrix(float* _values, int _rows, int _columns)
{
	rows = _rows;
	columns = _columns;

	InitializeArray(_values);
}

Matrix::Matrix(const Matrix& mat)
{
	rows = mat.rows;
	columns = mat.columns;

	values = new float[rows * columns];

	memcpy(values, mat.values, sizeof(float) * rows * columns);
}

Matrix::~Matrix()
{
	delete[] values;
}


Matrix Matrix::Copy()
{
	return Matrix(values, rows, columns);
}

void Matrix::Copy(float* output_location)
{
	memcpy(output_location, values, sizeof(float) * rows * columns);
}

bool Matrix::Equals(Matrix mat)
{
	if (rows != mat.rows || columns != mat.columns)
		return false;

	for (int i = 0; i < rows * columns; i++)
		if (values[i] != mat.values[i])
			return false;

	return true;
}

int Matrix::GetRows()
{
	return rows;
}

int Matrix::GetColumns()
{
	return columns;
}

float Matrix::GetValue(int row, int column)
{
	if (row >= rows || column >= columns)
		throw std::invalid_argument("Row or Column is Out of Bounds.");
	return values[row * columns + column];
}

std::string Matrix::ToString()
{
	std::string output = "";
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			output += std::to_string(values[y * columns + x]) + " ";
		}
		output += "\n";
	}

	return output;
}


// Used for rule of three.  If it weren't for the fact that I'm designing this
// to be compatible with Cuda (which requires standard arrays for memcpy) I
// would have used vectors, but it just doesn't work.  I think there may be
// a cuda implementation of std::vector, but its a little bit above my paygrade
// since this is being done in between classes.
Matrix& Matrix::operator=(const Matrix& mat)
{
	rows = mat.rows;
	columns = mat.columns;

	values = new float[rows * columns];

	memcpy(values, mat.values, sizeof(float) * rows * columns);

	return *this;
}

Matrix Matrix::operator+(Matrix mat)
{
	if (rows != mat.rows || columns != mat.columns)
		throw std::invalid_argument("Rows and Columns must be equal to add.");

	Matrix output = Matrix(rows, columns);
	for (int i = 0; i < rows * columns; i++)
		output.values[i] = values[i] + mat.values[i];

	return output;
}

Matrix Matrix::operator-(Matrix mat)
{
	if (rows != mat.rows || columns != mat.columns)
		throw std::invalid_argument("Rows and Columns must be equal to add.");

	Matrix output = Matrix(rows, columns);
	for (int i = 0; i < rows * columns; i++)
		output.values[i] = values[i] - mat.values[i];

	return output;
}

// This uses a simple O(n^3) algorithm, as most matrix multiplications done in
// this engine are of 4x4 and 4x1 matrices, which is less efficient with the
// Strassen algorithm.
Matrix Matrix::operator*(Matrix mat)
{
	if (columns != mat.rows)
		throw std::invalid_argument("Matrix sizes are ineligible to multiply.");

	float sum;
	Matrix output = Matrix(rows, mat.columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < mat.columns; j++)
		{
			sum = 0;
			for (int k = 0; k < mat.rows; k++)
			{
				sum += values[i * columns + k] * mat.values[k * mat.columns + j];
			}

			output.values[i * output.columns + j] = sum;
		}
	}

	return output;
}

void Matrix::Add(float* mat1, int mat1_rows, int mat1_columns,
				 float* mat2, int mat2_rows, int mat2_columns,
				 float* output_location)
{
	if (mat1_rows != mat2_rows || mat1_columns != mat2_columns)
		throw std::invalid_argument("Columns and rows must be equal to add.");

	for (int i = 0; i < mat1_rows * mat1_columns; i++)
	{
		output_location[i] = mat1[i] + mat2[i];
	}
}

void Matrix::Subtract(float* mat1, int mat1_rows, int mat1_columns,
					  float* mat2, int mat2_rows, int mat2_columns,
					  float* output_location)
{
	if (mat1_rows != mat2_rows || mat1_columns != mat2_columns)
		throw std::invalid_argument("Columns and rows must be equal to add.");

	for (int i = 0; i < mat1_rows * mat1_columns; i++)
	{
		output_location[i] = mat1[i] - mat2[i];
	}
}


void Matrix::Multiply(float* mat1, int mat1_rows, int mat1_columns,
		 float* mat2, int mat2_rows, int mat2_columns,
		 float* output_location)
{
	if (mat1_columns != mat2_rows)
		throw std::invalid_argument("Columns of mat1 must be equal to rows of mat2");

	float sum;
	for (int i = 0; i < mat1_rows; i++)
	{
		for (int j = 0; j < mat2_columns; j++)
		{
			sum = 0;
			for (int k = 0; k < mat2_rows; k++)
			{
				sum += mat1[i * mat1_columns + k] * mat2[k * mat2_columns + j];
			}

			output_location[i * mat2_columns + j] = sum;
		}
	}
}


// If values were not provided (default constructor or defined size constructor)
// then we don't pass in given_values.
void Matrix::InitializeArray(float* _values)
{
	values = new float[rows * columns];

	if (_values == nullptr)
		return;

	for (int i = 0; i < rows * columns; i++)
		values[i] = _values[i];
}
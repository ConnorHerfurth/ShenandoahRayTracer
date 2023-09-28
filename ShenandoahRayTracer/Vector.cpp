
#include "Vector.h"

// Vector2 Implementation
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2::Vector2(float* vector_location)
{
	x = vector_location[0];
	y = vector_location[1];
}

Vector2 Vector2::Copy()
{
	return Vector2(x, y);
}

void Vector2::Copy(float* output_location)
{
	output_location[0] = x;
	output_location[1] = y;
}

bool Vector2::Equals(Vector2 vec)
{
	return x == vec.x && y == vec.y;
}

float Vector2::GetMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

std::string Vector2::ToString()
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

Vector2 Vector2::operator+(Vector2 vec)
{
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator+(float f)
{
	return Vector2(x + f, y + f);
}

Vector2 Vector2::operator-(Vector2 vec)
{
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator-(float f)
{
	return Vector2(x - f, y - f);
}

Vector2 Vector2::operator*(float f)
{
	return Vector2(x * f, y * f);
}

Vector2 Vector2::operator/(float f)
{
	return Vector2(x / f, y / f);
}

float Vector2::GetAngle(Vector2 vec1, Vector2 vec2)
{
	return acos(Dot(vec1, vec2) / sqrt(vec1.GetMagnitude() * vec2.GetMagnitude()));
}

float Vector2::GetAngle(float* vec1, float* vec2)
{
	return acos(Dot(vec1, vec2) / (GetMagnitude(vec1) * GetMagnitude(vec2)));
}

float Vector2::GetDistance(Vector2 vec1, Vector2 vec2)
{
	return (vec1 - vec2).GetMagnitude();
}

float Vector2::GetDistance(float* vec1, float* vec2)
{
	return sqrt(pow(vec1[0] - vec2[0], 2) + pow(vec1[1] - vec2[1], 2));
}

float Vector2::Dot(Vector2 vec1, Vector2 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float Vector2::Dot(float* vec1, float* vec2)
{
	return vec1[0] * vec2[0] + vec1[1] * vec2[1];
}

float Vector2::GetMagnitude(float* vec)
{
	return sqrt(pow(vec[0], 2) + pow(vec[1], 2));
}

Vector2 Vector2::Normalize(Vector2 vec)
{
	return vec / vec.GetMagnitude();
}

void Vector2::Normalize(float* vec, float* output_location)
{
	float magnitude = GetMagnitude(vec);

	output_location[0] = output_location[0] / magnitude;
	output_location[1] = output_location[1] / magnitude;
	output_location[2] = output_location[2] / magnitude;
}

Vector2 Vector2::Project(Vector2 vec1, Vector2 vec2)
{
	return vec2 * Dot(vec1, vec2) / pow(vec2.GetMagnitude(), 2);
}

void Vector2::Project(float* vec1, float* vec2, float* output_location)
{
	MultiplyF(vec2, Dot(vec1, vec2), output_location);
	DivideF(output_location, pow(GetMagnitude(vec2), 2), output_location);
}

void Vector2::Add(float* vec1, float* vec2, float* output_location)
{
	output_location[0] = vec1[0] + vec2[0];
	output_location[1] = vec1[1] + vec2[1];
	output_location[2] = vec1[2] + vec2[2];
}

void Vector2::AddF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] + f;
	output_location[1] = vec1[1] + f;
	output_location[2] = vec1[2] + f;
}

void Vector2::Subtract(float* vec1, float* vec2, float* output_location)
{
	output_location[0] = vec1[0] - vec2[0];
	output_location[1] = vec1[1] - vec2[1];
	output_location[2] = vec1[2] - vec2[2];
}

void Vector2::SubtractF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] - f;
	output_location[1] = vec1[1] - f;
	output_location[2] = vec1[2] - f;
}

void Vector2::MultiplyF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] * f;
	output_location[1] = vec1[1] * f;
	output_location[2] = vec1[2] * f;
}

void Vector2::DivideF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] / f;
	output_location[1] = vec1[1] / f;
	output_location[2] = vec1[2] / f;
}

// Vector3 Impelementation
Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y; 
	z = _z;
}

// Initializes a Vector3 from a float array
Vector3::Vector3(float* vector_location)
{
	x = vector_location[0];
	y = vector_location[1];
	z = vector_location[2];
}

// Creates a deep copy so that scope can be maintained.
Vector3 Vector3::Copy()
{
	return Vector3(x, y, z);
}

void Vector3::Copy(float* output_location)
{
	output_location[0] = x;
	output_location[1] = y;
	output_location[2] = z;
}

bool Vector3::Equals(Vector3 vec)
{
	return x == vec.x && y == vec.y && z == vec.z;
}

float Vector3::GetMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

std::string Vector3::ToString()
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + "," +
		   std::to_string(z) + ")";
}

Vector3 Vector3::operator+(Vector3 vec)
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator+(float f)
{
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(Vector3 vec)
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator-(float f)
{
	return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator*(float f)
{
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(float f)
{
	return Vector3(x / f, y / f, z / f);
}

float Vector3::GetAngle(Vector3 vec1, Vector3 vec2)
{
	return Dot(vec1, vec2) / (vec1.GetMagnitude() * vec2.GetMagnitude());
}

float Vector3::GetAngle(float* vec1, float* vec2)
{
	return Dot(vec1, vec2) / (GetMagnitude(vec1) * GetMagnitude(vec2));
}

float Vector3::GetDistance(Vector3 vec1, Vector3 vec2)
{
	return sqrt(pow(vec2.x - vec1.x, 2) + 
		        pow(vec2.y - vec1.y, 2) + 
		        pow(vec2.z - vec1.z, 2));
}

float Vector3::GetDistance(float* vec1, float* vec2)
{
	return sqrt(pow(vec2[0] - vec1[0], 2) +
				pow(vec2[1] - vec1[1], 2) +
				pow(vec2[2] - vec1[2], 2));
}

float Vector3::Dot(Vector3 vec1, Vector3 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float Vector3::Dot(float* vec1, float* vec2)
{
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

float Vector3::GetMagnitude(float* vec)
{
	return sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
}

Vector3 Vector3::Cross(Vector3 vec1, Vector3 vec2)
{
	return Vector3(vec1.y * vec2.z - vec1.z * vec2.y,
				   vec1.z * vec2.x - vec1.x * vec2.z,
				   vec1.x * vec2.y - vec1.y * vec2.x);
}

void Vector3::Cross(float* vec1, float* vec2, float* output_location)
{
	output_location[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	output_location[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	output_location[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

Vector3 Vector3::Normalize(Vector3 vec)
{
	return vec / vec.GetMagnitude();
}

void Vector3::Normalize(float* vec1, float* output_location)
{
	float m = GetMagnitude(vec1);
	output_location[0] = output_location[0] / m;
	output_location[1] = output_location[1] / m;
	output_location[2] = output_location[2] / m;
}

// Calculates and returns the projection vector, in the format
// proju(v), where u = vec1 and v = vec2.
Vector3 Vector3::Project(Vector3 vec1, Vector3 vec2)
{
	return vec1 * (Dot(vec1, vec2) / pow(vec1.GetMagnitude(), 2));
}

// Same as previous method, but in-place.
void Vector3::Project(float* vec1, float* vec2, float* output_location)
{
	float d = Dot(vec1, vec2);
	float p = pow(GetMagnitude(vec1), 2);

	MultiplyF(vec1, d / p, output_location);
}

// These operator equivalents allow for you to do the same operators as before
// but in place, so it can be done over large array sets.  All of these are safe
// for saving to the same pointers that are provided for data.
void Vector3::Add(float* vec1, float* vec2, float* output_location)
{
	output_location[0] = vec1[0] + vec2[0];
	output_location[1] = vec1[1] + vec2[1];
	output_location[2] = vec1[2] + vec2[2];
}

void Vector3::AddF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] + f;
	output_location[1] = vec1[1] + f;
	output_location[2] = vec1[2] + f;
}

void Vector3::Subtract(float* vec1, float* vec2, float* output_location)
{
	output_location[0] = vec1[0] - vec2[0];
	output_location[1] = vec1[1] - vec2[1];
	output_location[2] = vec1[2] - vec2[2];
}

void Vector3::SubtractF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] - f;
	output_location[1] = vec1[1] - f;
	output_location[2] = vec1[2] - f;
}

void Vector3::MultiplyF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] * f;
	output_location[1] = vec1[1] * f;
	output_location[2] = vec1[2] * f;
}

void Vector3::DivideF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] / f;
	output_location[1] = vec1[1] / f;
	output_location[2] = vec1[2] / f;
}
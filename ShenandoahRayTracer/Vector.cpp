
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

bool Vector2::Equals(Vector2 vec, float epsilon)
{
	return abs(x - vec.x) < epsilon &&
		   abs(y - vec.y) < epsilon;
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
	return acos(Dot(vec1, vec2) / (vec1.GetMagnitude() * vec2.GetMagnitude()));
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

	output_location[0] = vec[0] / magnitude;
	output_location[1] = output_location[1] / magnitude;
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
}

void Vector2::AddF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] + f;
	output_location[1] = vec1[1] + f;
}

void Vector2::Subtract(float* vec1, float* vec2, float* output_location)
{
	float b = output_location[0];
	b = vec1[0];
	b = vec2[0];
	output_location[0] = vec1[0] - vec2[0];
	output_location[1] = vec1[1] - vec2[1];
}

void Vector2::SubtractF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] - f;
	output_location[1] = vec1[1] - f;
}

void Vector2::MultiplyF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] * f;
	output_location[1] = vec1[1] * f;
}

void Vector2::DivideF(float* vec1, float f, float* output_location)
{
	output_location[0] = vec1[0] / f;
	output_location[1] = vec1[1] / f;
}

// Vector3 Implementation
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

Vector3::Vector3(float* vector_location)
{
	x = vector_location[0];
	y = vector_location[1];
	z = vector_location[2];
}

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

bool Vector3::Equals(Vector3 vec, float epsilon)
{
	return abs(x - vec.x) <= epsilon &&
		   abs(y - vec.y) <= epsilon && 
		   abs(z - vec.z) <= epsilon;
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

bool Vector3::Equals(float* vec1, float* vec2, float epsilon)
{
	return  abs(vec1[0] - vec2[0]) <= epsilon &&
			abs(vec1[1] - vec2[1]) <= epsilon &&
			abs(vec1[2] - vec2[2]) <= epsilon;
}

float Vector3::GetAngle(Vector3 vec1, Vector3 vec2)
{
	return acos(Dot(vec1, vec2) / (vec1.GetMagnitude() * vec2.GetMagnitude()));
}

float Vector3::GetAngle(float* vec1, float* vec2)
{
	return acos(Dot(vec1, vec2) / (GetMagnitude(vec1) * GetMagnitude(vec2)));
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
	output_location[0] = vec1[0] / m;
	output_location[1] = vec1[1] / m;
	output_location[2] = vec1[2] / m;
}

Vector3 Vector3::Project(Vector3 u, Vector3 v)
{
	return u * (Dot(u, v) / pow(u.GetMagnitude(), 2));
}

void Vector3::Project(float* u, float* v, float* output_location)
{
	float d = Dot(u, v);
	float p = pow(GetMagnitude(u), 2);

	MultiplyF(u, d / p, output_location);
}

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
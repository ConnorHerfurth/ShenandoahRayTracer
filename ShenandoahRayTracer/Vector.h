#pragma once

#include <string>
#include <format>
#include <math.h>

/// <summary>
/// 2D mathematical vector, mostly used for UV texture coordinates.
/// </summary>
class Vector2 {
public:
	float x, y;

	Vector2();
	Vector2(float _x, float _y);
	Vector2(float* vector_location);

	// Non-Static Methods
	Vector2 Copy();
	void Copy(float* output_location);
	bool Equals(Vector2 vec);
	float GetMagnitude();
	std::string ToString();

	// Operators
	Vector2 operator+(Vector2 vec);
	Vector2 operator+(float f);
	Vector2 operator-(Vector2 vec);
	Vector2 operator-(float f);
	Vector2 operator*(float f);
	Vector2 operator/(float f);

	// Static Methods
	static float GetAngle(Vector2 vec1, Vector2 vec2);
	static float GetAngle(float* vec1, float* vec2);
	static float GetDistance(Vector2 vecc1, Vector2 vec2);
	static float GetDistance(float* vec1, float* vec2);
	static float Dot(Vector2 vec1, Vector2 vec2);
	static float Dot(float* vec1, float* vec2);
	static float GetMagnitude(float* vec);

	static Vector2 Normalize(Vector2 vec);
	static void Normalize(float* vec, float* output_location);
	static Vector2 Project(Vector2 vec1, Vector2 vec2);
	static void Project(float* vec1, float* vec2, float* output_location);

	// Static Operator Equivalents for use in Arrays
	static void Add(float* vec1, float* vec2, float* output_location);
	static void AddF(float* vec1, float f, float* output_location);
	static void Subtract(float* vec1, float* vec2, float* output_location);
	static void SubtractF(float* vec1, float f, float* output_location);
	static void MultiplyF(float* vec1, float f, float* output_location);
	static void DivideF(float* vec1, float f, float* output_location);
};

/** Implementation of a 3D Mathematical Vector

The Vector3 class is used to both encapsulate 3D vector information and
operations easily, as well as providing methods for performing vector math
on arrays of floats.  The float array methods are important because it allows
for us to sperform operations easily on the massive amounts of geometry data
that are associated with the scenes.

*/
class Vector3 {
public:
	float x, y, z;

	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(float* vector_location);

	// Non-Static Methods
	Vector3 Copy();
	void Copy(float* output_location);
	bool Equals(Vector3 vec);
	float GetMagnitude();
	std::string ToString();

	// Operators
	Vector3 operator+(Vector3 vec);
	Vector3 operator+(float f);
	Vector3 operator-(Vector3 vec);
	Vector3 operator-(float f);
	Vector3 operator*(float f);
	Vector3 operator/(float f);

	// Static Methods
	static float GetAngle(Vector3 vec1, Vector3 vec2);
	static float GetAngle(float* vec1, float* vec2);
	static float GetDistance(Vector3 vec1, Vector3 vec2);
	static float GetDistance(float* vec1, float* vec2);
	static float Dot(Vector3 vec1, Vector3 vec2);
	static float Dot(float* vec1, float* vec2);
	static float GetMagnitude(float* vec);

	static Vector3 Cross(Vector3 vec1, Vector3 vec2);
	static void Cross(float* vec1, float* vec2, float* output_location);
	static Vector3 Normalize(Vector3 vec);
	static void Normalize(float* vec1, float* output_location);
	static Vector3 Project(Vector3 vec1, Vector3 vec2);
	static void Project(float* vec1, float* vec2, float* output_location);

	// Static Operator Equivalents for use in Arrays
	static void Add(float* vec1, float* vec2, float* output_location);
	static void AddF(float* vec1, float f, float* output_location);
	static void Subtract(float* vec1, float* vec2, float* output_location);
	static void SubtractF(float* vec1, float f, float* output_location);
	static void MultiplyF(float* vec1, float f, float* output_location);
	static void DivideF(float* vec1, float f, float* output_location);

};
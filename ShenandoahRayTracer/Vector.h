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

	/**
	* @brief Default constructor for Vector3
	*/
	Vector3();
	/**
	* @brief Vector3 constructor with specified values
	* 
	* @param _x: Vector x component
	* @param _y: Vector y component
	* @param _z: Vector z component
	*/
	Vector3(float _x, float _y, float _z);
	/**
	* @brief Vector3 constructor that loads from position in float array.
	* 
	* @param vector_location: Pointer to float array with minimum size 3.
	*/
	Vector3(float* vector_location);

	// Non-Static Methods
	/**
	* @brief Copies the Vector3
	*
	* @return A copy of the Vector3
	*/
	Vector3 Copy();
	/**
	* @brief Copies the Vector3 to a float array.
	* 
	* @param output_location: Pointer to a float array with minimum size 3.
	*/
	void Copy(float* output_location);
	/**
	* @brief Checks if two Vector3 have all equivalent components.
	* 
	* @param vec: A Vector3 to check equivalence.
	* 
	* @return Whether the two Vector3 are equivalent.
	*/
	bool Equals(Vector3 vec, float epsilon);
	/**
	* @brief Returns the magnitude of the Vector3
	* 
	* @return The magnitude of the vector.
	*/
	float GetMagnitude();
	/**
	* @brief Returns a string representation of the Vector3
	* 
	* @return A string representation of the Vector3
	*/
	std::string ToString();

	// Operators
	Vector3 operator+(Vector3 vec);
	Vector3 operator+(float f);
	Vector3 operator-(Vector3 vec);
	Vector3 operator-(float f);
	Vector3 operator*(float f);
	Vector3 operator/(float f);

	static bool Equals(float* vec1, float* vec2, float epsilon);

	// Static Methods
	/**
	* @brief Returns the angle between two Vector3
	* 
	* @param vec1: The first vector
	* @param vec2: The second vector
	* 
	* @return The angle between the two vectors, in 
	*/
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
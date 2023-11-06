#pragma once

#include <string>
#include <format>
#include <math.h>

/** Implementation of a 2D Mathematical Vector

The Vector2 class is used to both encapsulate 2D vector information and
operations easily, as well as providing methods for performing vector math
on arrays of floats.

*/
class Vector2 {
public:
	float x, y;

	/**
	* @brief Default constructor for Vector2.
	*/
	Vector2();
	/**
	* @brief Vector2 constructor with specified values.
	* 
	* @param _x: The x component of the vector.
	* @param _y: The y component of the vector.
	*/
	Vector2(float _x, float _y);
	/**
	* @brief Vector2 constructor that loads from pointer to float array.
	* 
	* @param vector_location: A pointer to a float array with minimum size 2.
	*/
	Vector2(float* vector_location);

	// Non-Static Methods
	/**
	* @brief Returns a deep copy of the Vector2.
	* 
	* @return A deep copy of the vector.
	*/
	Vector2 Copy();
	/**
	* @brief Copies the Vector2 to a float array.
	* 
	* @param output_location: A pointer to a float array with minimum size 2.
	*/
	void Copy(float* output_location);
	/**
	* @brief Checks if two Vector2 have all equivalent components, within an
	* epsilon.
	* 
	* @param vec: A Vector2 to check equivalence.
	* @param epsilon: A floating point epsilon.
	* 
	* @return True if they're equal, false otherwise.
	*/
	bool Equals(Vector2 vec, float epsilon);
	/**
	* @brief Returns the magnitude of the vector.
	* 
	* @return The magnitude of the vector.
	*/
	float GetMagnitude();
	/**
	* @brief Returns a string representation of the vector.
	* 
	* @returns A string representation of the vector.
	*/
	std::string ToString();

	// Operators
	Vector2 operator+(Vector2 vec);
	Vector2 operator+(float f);
	Vector2 operator-(Vector2 vec);
	Vector2 operator-(float f);
	Vector2 operator*(float f);
	Vector2 operator/(float f);

	// Static Methods
	/**
	* @brief Returns the angle between two Vector2.
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @return The angle between the vectors, in radians.
	*/
	static float GetAngle(Vector2 vec1, Vector2 vec2);
	/**
	* @brief Returns the angle between two vector arrays.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* 
	* @return The angle between the vectors, in radians.
	*/
	static float GetAngle(float* vec1, float* vec2);
	/**
	* @brief Returns the distance between two Vector2, treating them as points.
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @return The distance between the vectors, in units.
	*/
	static float GetDistance(Vector2 vec1, Vector2 vec2);
	/**
	* @brief Returns the distance between two vector arrays, treating them as
	* points.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* 
	* @return The distance between the vectors, in units.
	*/
	static float GetDistance(float* vec1, float* vec2);
	/**
	* @brief Returns the dot product of the two Vector2.
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @return The dot product of the vectors.
	*/
	static float Dot(Vector2 vec1, Vector2 vec2);
	/**
	* @brief Returns the dot product of two vector arrays.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* 
	* @return The dot product of the vectors.
	*/
	static float Dot(float* vec1, float* vec2);
	/**
	* @brief Returns the magnitude of a vector array.
	* 
	* @param vec: Pointer to a float array with minimum size 2.
	* 
	* @return The magnitude of the vector.
	*/
	static float GetMagnitude(float* vec);

	/**
	* @brief Returns a normalized version of the vector, or a vector where the
	* magnitude is 1.
	* 
	* @param vec: The vector to be normalized.
	* 
	* @return The normalized vector.
	*/
	static Vector2 Normalize(Vector2 vec);
	/**
	* @brief Calculates and stores a normalized version of the vector, or a
	* vector where the magnitude is 1.  Can be done in-place.
	* 
	* @param vec: Pointer to a float array with minimum size 2.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void Normalize(float* vec, float* output_location);
	/**
	* @brief Returns the projection vector, proju(v), or the 
	* projection of u onto v.
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @return The projection vector proju(v).
	*/
	static Vector2 Project(Vector2 vec1, Vector2 vec2);
	/**
	* @brief Calculates and stores the projection vector, proju(v), or the
	* projection of u onto v, using float arrays.  Cannot be done in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores the result in 'output_location'.
	*/
	static void Project(float* vec1, float* vec2, float* output_location);

	// Static Operator Equivalents for use in Arrays
	/**
	* @brief Adds two vector arrays.  Can be done in place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void Add(float* vec1, float* vec2, float* output_location);
	/**
	* @brief Adds a vector array and a float.  Can be done in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param f: Float to be added.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void AddF(float* vec1, float f, float* output_location);
	/**
	* @brief Subtracts two vector arrays, like (vec1 - vec2).  Can be done 
	* in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param vec2: Pointer to a float array with minimum size 2.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void Subtract(float* vec1, float* vec2, float* output_location);
	/**
	* @brief Subtracts a vector array and a float, like (vec1 - f).  Can be 
	* done in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param f: Float to be subtracted.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void SubtractF(float* vec1, float f, float* output_location);
	/**
	* @brief Multiplies a vector array and a float.  Can be done in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param f: Float to be multiplied.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void MultiplyF(float* vec1, float f, float* output_location);
	/**
	* @brief Divides a vector array by a float.  Can be done in-place.
	* 
	* @param vec1: Pointer to a float array with minimum size 2.
	* @param f: Float to divide by.
	* @param output_location: Pointer to a float array with minimum size 2,
	* where output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
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
	* @param epsilon: A floating point epsilon, which avoids incorrect 'false'
	* returns.
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

	/**
	* @brief Returns whether two vector arrays are equal, within an epsilon.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* @param epsilon: A floating point epsilon, which avoids incorrect 'false'
	* returns.
	* 
	* @return Whether the two vectors were equal
	*/
	static bool Equals(float* vec1, float* vec2, float epsilon);

	// Static Methods
	/**
	* @brief Returns the angle between two Vector3
	* 
	* @param vec1: The first vector
	* @param vec2: The second vector
	* 
	* @return The angle between the two Vector3, in radians
	*/
	static float GetAngle(Vector3 vec1, Vector3 vec2);
	/**
	* @brief Returns the angle between two Vector3 arrays
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* 
	* @returns The angle between the two vectors, in radians.
	*/
	static float GetAngle(float* vec1, float* vec2);
	/**
	* @brief Returns the distance between two Vector3
	* 
	* @param vec1: The first vector
	* @param vec2: The second vector
	* 
	* @return The distance between the two Vector3.  Unit is dependent on the
	* unit of the vectors.
	*/
	static float GetDistance(Vector3 vec1, Vector3 vec2);
	/**
	* @brief Returns the distance between two vector arrays.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* 
	* @return The distance between the two vectors.  Unit is dependent on the
	* unit of the vectors.
	*/
	static float GetDistance(float* vec1, float* vec2);
	/**
	* @brief Returns the dot product of two Vector3
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @returns The dot product of both Vector3.
	*/
	static float Dot(Vector3 vec1, Vector3 vec2);
	/**
	* @brief Returns the dot product of two vector arrays.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* 
	* @return The dot product of both vectors.
	*/
	static float Dot(float* vec1, float* vec2);
	/**
	* @brief Returns the magnitude of a vector array.
	* 
	* @param vec: A pointer to a float array with minimum size 3.
	* 
	* @return The magnitude of the vector.
	*/
	static float GetMagnitude(float* vec);

	/**
	* @brief Returns the cross product of two Vector3.
	* 
	* @param vec1: The first vector.
	* @param vec2: The second vector.
	* 
	* @return The cross product of the two vectors.
	*/
	static Vector3 Cross(Vector3 vec1, Vector3 vec2);
	/**
	* @brief Calculates and stores the cross product of two vector arrays.
	* Cannot be done in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'.
	*/
	static void Cross(float* vec1, float* vec2, float* output_location);
	/**
	* @brief Returns a normalized version of a Vector3, or version of Vector3
	* that has a magnitude of 1.
	* 
	* @param vec: The vector to be normalized.
	* 
	* @return A new Vector3 that is a normalized version of 'vec'
	*/
	static Vector3 Normalize(Vector3 vec);
	/**
	* @brief Calculates and stores the normalized version of a vector array.
	* Can be done in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* @param output_location: A pointer to a float array with minimum size 3
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void Normalize(float* vec1, float* output_location);
	/**
	* @brief Returns the projection vector, proju(v), or the projection of u
	* onto v.
	* 
	* @param u: The u vector of the projection
	* @param v: The v vector of the projection
	* 
	* @returns A new Vector3 that is the projection of u onto v.
	*/
	static Vector3 Project(Vector3 u, Vector3 v);
	/**
	* @brief Calculates and stores the projection vector, proju(v), or the 
	* projection of u onto v, using float arrays.  Cannot be done in-place.
	* 
	* @param u: A pointer to a float array with minimum size 3.
	* @param v: A pointer to a float array with minimum size 3.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void Project(float* u, float* v, float* output_location);

	// Static Operator Equivalents for use in Arrays
	/**
	* @brief Adds two vector arrays.  Can be done in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void Add(float* vec1, float* vec2, float* output_location);
	/**
	* @brief Adds a float to a vector array component-wise.  Can be done 
	* in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param f: The value to be added.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void AddF(float* vec1, float f, float* output_location);
	/**
	* @brief Subtracts two vector arrays.  Can be done in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param vec2: A pointer to a float array with minimum size 3.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void Subtract(float* vec1, float* vec2, float* output_location);
	/**
	* @brief Subtracts a float from a vector array component-wise.  Can be done
	* in-place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param f: The value to be subtracted.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void SubtractF(float* vec1, float f, float* output_location);
	/**
	* @brief Multiplies a float to a vector array component-wise.  Can be done
	* in place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param f: The value to be multiplied.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void MultiplyF(float* vec1, float f, float* output_location);
	/**
	* @brief Divides a float from a vector array component-wise.  Can be done
	* in place.
	* 
	* @param vec1: A pointer to a float array with minimum size 3.
	* @param f: The value to be divided by.
	* @param output_location: A pointer to a float array with minimum size 3,
	* where the output data can be written.
	* 
	* @return None, but stores result in 'output_location'
	*/
	static void DivideF(float* vec1, float f, float* output_location);

};
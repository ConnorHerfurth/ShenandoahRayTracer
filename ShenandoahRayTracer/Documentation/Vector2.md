# Vector 2
The Vector2 class is used to store and calculate values relating to 2D points and directions, especially in UV transformations.

## Vector2 vs Vector Array Methods
Similar to Vector3, Vector2 takes advantage of arrays to store large amounts of Vector2 without the class and method call overhead.  Many of the static methods that accept pointers are simply alternative methods for Vector2 methods that operate on arrays.  Arrays must be passed as pointers to arrays with a minimum size of 2, depending on the method.  Some can be done in place, as specified in the documentation.  If it says it cannot be done in place, assume that it cannot.  Where float pointers can be found, it can be assumed that they need a minimum size two, unless otherwise specified.

## Public Variables
 - float x, y : The individual components of the Vector2.

## Constructors
 - Vector2()
   - Default constructor for Vector2.
   - Should be used for uninitialized values or defaul values where the vector should be the origin.
 - Vector2(float _x, float _y)
   - Vector2 constructor with specified values.
   - Creates a vector two with two already defined values.
 - Vector2(float* vector_location)
   - Vector2 constructor that loads from position in float array.
   - Creates a vector from a floating point array, where the array must have a minimum size of two after the pointer.  Should be used when a value within an array (generally an array of multiple vectors) needs to be converted back to an actual Vector2.

## Non-Static Methods
 - Vector2 Copy()
   - Returns a deep copy of the vector.
 - void Copy(float* output_location)
   - Places a deep copy of the vector at a floating point array.  output_location must be minimum size two.
 - bool Equals(Vector3 vec, float epsilon)
   - Returns whether or not two vectors are equal.  The epsilon serves to make sure that the values are at least close to equal, since the values are floating point.  Tested epsilon is 0.00001f.
 - float GetMagnitude()
   - Returns the magnitude of a vector, i.e. the distance from the origin to the vector if it is a point, or the length of the vector if it is a direction.
 - std::string ToString()
   - Returns a string representation of the vector, in the format '(x, y)'.

## Static Methods
- float GetAngle(Vector2 vec1, Vector2 vec2)
  - Returns the angle, in radians, between two vectors.  Treats the vectors as direction vectors, not as points.
- float GetAngle(float* vec1, float* vec2)
  - Returns the angle, in radians, between two vector arrays.  Treats the vectors as direction vectors, not as points.
- float GetDistance(Vector2 vec1, Vector2 vec2)
  - Returns the distance, between two vectors.  Treats the vectors as points, not as direction vectors.
- float GetDistance(float* vec1, float* vec2)
  - Returns the distance, between two vector arrays.  Treats the vectors as points, not as direction vectors.
- float Dot(Vector2 vec1, Vector2 vec2)
  - Returns the dot product of two vectors.
- float Dot(float* vec1, float* vec2)
  - Returns the dot product of two vector arrays.
- float GetMagnitude(float* vec)
  - Returns the magnitude of a vector array, i.e. the distance from the origin to the vector if it is a point, or the length of the vector if it is a direction.
- Vector2 Normalize(Vector2 vec)
  - Returns the normalized version of vec, or 'vec / |vec|'
- void Normalize(float* vec1, float* output_location)
  - Calculates and stores the  normalized version of vec, or 'vec / |vec|', to output_location.  Can be done in place.
- void Project(Vector2 u, Vector2 v)
  - Returns the projection vector of u onto v, or proju(v).
- void Project(float* u, float* v, float* output_location)
  - Calculates and stores the projection vector of u onto v, or proju(v), to output_location.  Cannot be done in-place.
- void Add(float* vec1, float* vec2, float* output_location)
  - Calculates and stores the component-wise addition of both vector arrays into output_location.  Can be done in-place.
- void AddF(float* vec1, float f, float* output_location)
  - Calculates and stores the component-wise addition of the vector array and the float into output_location.  Can be done in-place.
- void Subtract(float* vec1, float* vec2, float* output_location)
  - Calculates and stores the component-wise difference of the vector array and the float into output_location (vec1 - vec2).  Can be done in-place.
- void SubtractF(float* vec1, float f, float* output_location)
  - Calculates and stores the component-wise difference of the vector array and the float into output_location (vec1 - f).  Can be done in place.
- void MultiplyF(float* vec1, float f, float* output_location)
  - Calculates and stores the component-wise product of the vector array and float into output_location.  Can be done in-place.
- void DivideF(float* vec1, float f, float* output_location)
  - Calculates and stores the component-wise quotient of the vector array and float into output_location (vec1 / f).  Can be done in-place.

## Operators
 - Vector2 operator+(Vector2 vec)
 - Vector2 operator+(float f)
 - Vector2 operator-(Vector2 vec)
 - Vector2 operator-(float f)
 - Vector2 operator*(float f)
 - Vector2 operator/(float f)
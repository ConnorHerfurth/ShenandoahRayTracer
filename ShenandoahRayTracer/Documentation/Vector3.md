# Vector3
The Vector3 class is used to store and calculate values relating to 3D points and directions.  Also used in Transforms.

## Vector3 vs Vector Array Methods
To store large amounts of Vector3 with less memory and faster computation, large collections of Vector3 can be stored as floating point arrays.  Methods within this class differentiate between 'Vector3' and 'vector arrays', with the first being the class itself, and the second being a floating point array of size 3 or more.  These can be used to do operations much faster and store things much more effectively, without the need for copying vectors or having the issue of class overhead.  Where float pointers can be found, it can be assumed that they need to be minimum size three, unless otherwise specified.

## Public Variables
 - float x, y, z : The individual components of the Vector3


## Constructors
- Vector3()
  - Default constructor for Vector3.
  - Should be used for uninitialized values of default values where the vector should be the origin.
- Vector3(float _x, float _y, float _z)
  - Vector3 constructor with specified values.
  - Creates a vector three with three already defined values.
- Vector3(float* vector_location)
  - Vector3 constructor that loads from position in float array.
  - Creates a vector from a floating point array, where the array must have a minimum size of three after the pointer.  Should be used when a value within an array (generally an array of multiple vectors) needs to be converted back to an actual Vector3.

## Non-Static Methods
- Vector3 Copy()
  - Returns a deep copy of the vector.
- void Copy(float* output_location)
  - Places a deep copy of the vector at a floating point array.  output_location must be minimum size 3.
- bool Equals(Vector3 vec, float epsilon)
  - Returns whether or not two vectors are equal.  The epsilon serves to make sure that the values are at least close to equal, since the values are floating point.  Tested epsilon is 0.00001f.
- float GetMagnitude()
  - Returns the magnitude of a vector, i.e. the distance from the origin to the vector if it is a point, or the length of the vector if it is a direction.
- std::string ToString()
  - Returns a string representation of the vector, in the format '(x, y, z)'.  

## Static Methods
- bool Equals(float* vec1, float* vec2, float epsilon)
  - Returns whether or not two vector arrays are equal.  The epsilon serves to make sure that the values are at least close to equal, since the values are floating point.  Tested epsilon is 0.00001f.
- float GetAngle(Vector3 vec1, Vector3 vec2)
  - Returns the angle, in radians, between two vectors.  Treats the vectors as direction vectors, not as points.
- float GetAngle(float* vec1, float* vec2)
  - Returns the angle, in radians, between two vector arrays.  Treats the vectors as direction vectors, not as points.
- float GetDistance(Vector3 vec1, Vector3 vec2)
  - Returns the distance between two vectors.  Treats the vectors as points, not direction vectors.
- float GetDistance(float* vec1, float* vec2)
  - Returns the distance between two vector arrays.  Treats the vectors as points, not direction vectors.
- float Dot(Vector3 vec1, Vector3 vec2)
  - Returns the dot product of two vectors.  
- float Dot(float* vec1, float* vec2)
  - Returns the dot product of two vector arrays.
- float GetMagnitude(float* vec)
  - Returns the magnitude of a vector array.
- Vector3 Cross(Vector3 vec1, Vector3 vec2)
  - Returns the cross product of two Vector3.
- void Cross(float* vec1, float* vec2, float* output_location)
  - Stores the cross product of the two vector arrays to output_location.  Cannot be done in-place.
- Vector3 Normalize(Vector3 vec)
  - Returns the normalized version of vec, or 'vec / |vec|'
- void Normalize(float* vec1, float* output_location)
  - Stores the normalized version of vec, or 'vec / |vec|', in output_location.  This can be done in-place.
- Vector3 Project(Vector3 u, Vector3 v)
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
- Vector3 operator+(Vector3 vec)
- Vector3 operator+(float f)
- Vector3 operator-(Vector3 vec)
- Vector3 operator-(float f)
- Vector3 operator*(float f)
- Vector3 operator/(float f)
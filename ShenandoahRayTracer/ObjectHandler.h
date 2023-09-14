#pragma once

#include <string>
#include "Transform.h"

// Object handlers deal with the geometry, transform, and visuals of individual
// objects within the scene.
//
// This is a very bare bones implementation but thats all we need right now.
class ObjectHandler
{
public:
	Transform transform;
	std::string name;

	ObjectHandler();
	ObjectHandler(float* _vertices, int _num_vertices, int* _triangles, 
		          int _num_triangles, Transform t, std::string _name);
	ObjectHandler(const ObjectHandler& obj);
	~ObjectHandler();

	ObjectHandler& operator=(const ObjectHandler& obj);

	// Not called Copy because once its copied it has a different name.
	ObjectHandler Duplicate();
	
	// Can either copy the raw, relative vertices or the vertices after being
	// adjusted by the transform.
	//
	// If the object is exceedingly large or you're doing it on the GPU, a
	// possible method for getting it to go faster is to 
	void CopyRawVertices(float* output_location);
	void CopyAdjustedVertices(float* output_location);
	void CopyTriangles(int* output_location);

	//TODO: Design a system for having textures and shaders within the object.

	
private:
	float* vertices;
	int num_vertices;
	int* triangles;
	int num_triangles;

	void InitializeArrays(float* _vertices, int* _triangles);
};


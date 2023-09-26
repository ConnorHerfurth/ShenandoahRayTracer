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
	//TODO: Create a constructor that takes an obj file or equivalent format.
	~ObjectHandler();

	ObjectHandler& operator=(const ObjectHandler& obj);

	// Not called Copy because once its copied it has a different name.
	ObjectHandler Duplicate();

	int GetNumVertices();
	int GetNumTriangles();
	
	// Can either copy the raw, relative vertices or the vertices after being
	// adjusted by the transform.
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


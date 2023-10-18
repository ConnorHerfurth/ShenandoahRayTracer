#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
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

	/**
	* @brief Default constructor for ObjectHandlers
	*/
	ObjectHandler();

	/**
	* @brief Complex constructor for ObjectHandler.  Takes in multiple arrays
	* containing all the necessary geometric data.  Not recommended for use in
	* projects, except for dynamically generated objects or testing purposes.
	* 
	* @param _vertices A float pointer pointing to an array containing the
	* vertices of the object.  Will be copied.
	* @param _num_vertices The number of vertices in the object.
	* @param _uvs A float pointer pointing to an array containing the UVs of the
	* object.  Will be copied.
	* @param _num_uvs The number of UV coordinates in the object.
	* @param _triangles An int pointer pointing to an array containing the
	* triangles of the object.  Will be copied.
	* @param _num_triangles The number of triangles in the object.
	* @param _triangle_uvs An int pointer pointing to an array containing the
	* UVs of each triangle, with each value pointing to the index
	* of a UV for each vertice.  Will be copied.
	* @param t The Transform of the object.
	* @param _name The name of the object.
	*/
	ObjectHandler(float* _vertices, int _num_vertices, float* _uvs, int _num_uvs,
		          int* _triangles, int _num_triangles, int* _triangle_uvs,
		          Transform t, std::string _name);

	// TODO: Create a constructor that can load from a .obj file.

	/**
	* @brief Copy constructor for the ObjectHandler.  Copies all values over
	* and reinitializes arrays.
	* 
	* @param _obj The address of the ObjectHandler to be copied.
	*/
	ObjectHandler(const ObjectHandler& obj);

	/**
	* @brief Destructor for the ObjectHandler.  Deletes all dynamic arrays.
	*/
	~ObjectHandler();

	ObjectHandler& operator=(const ObjectHandler& obj);

	/**
	* @brief Duplicates the object by creating an entirely new ObjectHandler
	* with the same data.
	* 
	* @return An identical ObjectHandler with separate data.
	*/
	ObjectHandler Duplicate();

	int GetNumVertices();
	int GetNumTriangles();
	int GetNumUVs();
	
	/**
	* @brief Copies the vertices to a new location
	* 
	* @param output_location The location to be copied to.
	*/
	void CopyRawVertices(float* output_location);

	/**
	* @brief Copies the vertices to a new location after applying the transform
	* to them.
	* 
	* @param output_location The location to be copied to.
	*/
	void CopyAdjustedVertices(float* output_location);

	void CopyTriangles(int* output_location);
	void CopyTriangleUVs(int* output_location);
	void CopyUVs(float* output_location);

	//TODO: Design a system for having textures and shaders within the object.

private:
	float* vertices;
	int num_vertices;

	// UVs are handled in an interesting way since the code is designed to work
	// with wavefront files.  We create an array of n uv coordinates of size 2.
	// Then, there are two arrays of triangles, with the first representing the
	// indices of the three vertices, and the second representing the indices
	// of each uv.  This allows us to only concern ourselves with geometry when
	// we want to, and to deal with the uvs separately.
	int* triangles;
	int num_triangles;
	int* triangle_uvs;

	float* uvs;
	int num_uvs;

	/**
	* @brief Initializes the arrays by copying over the information.
	* 
	* @param _vertices A pointer to the vertices array to be copied.
	* @param _triangles A pointer to the triangles array to be copied.
	* @param _triangle_uvs A pointer to the triangle uv array to be copied.
	* @param _uvs A poitner to the uv array to be copied.
	*/
	void InitializeArrays(float* _vertices, int* _triangles,
		                  int* _triangle_uvs, float* _uvs);
};


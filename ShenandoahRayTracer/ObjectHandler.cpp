#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	transform = Transform();
	name = "Default Object Name";

	vertices = new float[1];
	num_vertices = 0;

	triangles = new int[1];
	triangle_uvs = new int[1];
	num_triangles = 0;

	uvs = new float[1];
	num_uvs = 0;
 }

ObjectHandler::ObjectHandler(float* _vertices, int _num_vertices, float* _uvs,
							 int _num_uvs, int* _triangles, int _num_triangles, 
							 int* _triangle_uvs, Transform t, std::string _name)
{
	transform = t;
	num_vertices = _num_vertices;
	num_triangles = _num_triangles;
	num_uvs = _num_uvs;

	InitializeArrays(_vertices, _triangles, _triangle_uvs, _uvs);

	name = _name;
}

ObjectHandler::ObjectHandler(const ObjectHandler& obj)
{
	transform = obj.transform;
	num_vertices = obj.num_vertices;
	num_uvs = obj.num_uvs;
	num_triangles = obj.num_triangles;


	InitializeArrays(obj.vertices, obj.triangles, obj.triangle_uvs, obj.uvs);

	name = obj.name;
}

ObjectHandler::~ObjectHandler()
{
	delete[] vertices;
	delete[] triangles;
	delete[] triangle_uvs;
	delete[] uvs;
}


ObjectHandler& ObjectHandler::operator=(const ObjectHandler& obj)
{
	// Deleting old vertices to avoid memory leak.
	delete[] vertices;
	delete[] triangles;
	delete[] triangle_uvs;
	delete[] uvs;

	num_vertices = obj.num_vertices;
	num_triangles = obj.num_triangles;
	num_uvs = obj.num_uvs;

	InitializeArrays(obj.vertices, obj.triangles, obj.triangle_uvs, obj.uvs);

	name = obj.name;

	return *this;
}

ObjectHandler ObjectHandler::Duplicate()
{
	return ObjectHandler(vertices, num_vertices, uvs, num_uvs, 
		                 triangles, num_triangles, triangle_uvs,
		                 transform, name + "_Copy");
}

int ObjectHandler::GetNumVertices()
{
	return num_vertices;
}

int ObjectHandler::GetNumTriangles()
{
	return num_triangles;
}

int ObjectHandler::GetNumUVs()
{
	return num_uvs;
}

void ObjectHandler::CopyRawVertices(float* output_location)
{
	// Since vertices in most common formats (obj, fbx, etc) put the vertices
	// in relation to the origin of the object, the transformations happen
	// with those values.  To make sure the original mesh is preserved in case
	// necessary, we store the raw vertices.  This method returns the raw verts
	// so that they can be used for other operations if necessary.
	memcpy(output_location, &vertices[0], sizeof(float) * num_vertices * 4);
}

void ObjectHandler::CopyAdjustedVertices(float* output_location)
{
	// In contrast, this method gets the transformation matrix and multiplies
	// it by the points so that the stored version is where they should be in
	// the real world.
	Matrix transformation_matrix = transform.GetCompositeMatrix();
	float matrix[16];

	transformation_matrix.Copy(&matrix[0]);

	for (int i = 0; i < num_vertices * 4; i += 4)
	{
		Matrix::Multiply(&vertices[i], 1, 4, &matrix[0], 4, 4, &output_location[i]);
	}
}

void ObjectHandler::CopyTriangles(int* output_location)
{
	// Unlike the vertices, there is no adjusted triangles, since the points in
	// the triangle represent indices within the vertice array.
	memcpy(output_location, triangles, sizeof(int) * num_triangles * 3);
}

void ObjectHandler::CopyTriangleUVs(int* output_location)
{
	memcpy(output_location, &triangle_uvs[0], sizeof(int) * num_triangles * 3);
}

void ObjectHandler::CopyUVs(float* output_location)
{
	memcpy(output_location, &uvs[0], sizeof(float) * num_uvs * 2);
}

void ObjectHandler::InitializeArrays(float* _vertices, int* _triangles, 
	                                 int* _triangle_uvs, float* _uvs)
{
	vertices = new float[num_vertices * 4];
	triangles = new int[num_triangles * 3];
	triangle_uvs = new int[num_triangles * 3];
	uvs = new float[num_uvs * 2];

	memcpy(vertices, _vertices, sizeof(float) * num_vertices * 4);
	memcpy(triangles, _triangles, sizeof(int) * num_triangles * 3);
	memcpy(triangle_uvs, _triangle_uvs, sizeof(int) * num_triangles * 3);
	memcpy(uvs, _uvs, sizeof(float) * num_uvs * 2);
}
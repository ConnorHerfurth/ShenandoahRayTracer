#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	transform = Transform();
	name = "Default Object Name";

	vertices = new float[1];
	num_vertices = 0;
	triangles = new int[1];
	num_triangles = 0;
 }

ObjectHandler::ObjectHandler(float* _vertices, int _num_vertices, int* _triangles,
							 int _num_triangles, Transform t, std::string _name)
{
	transform = t;
	num_vertices = _num_vertices;
	num_triangles = _num_triangles;

	InitializeArrays(_vertices, _triangles);

	name = _name;
}

ObjectHandler::ObjectHandler(const ObjectHandler& obj)
{
	num_vertices = obj.num_vertices;
	num_triangles = obj.num_triangles;

	InitializeArrays(obj.vertices, obj.triangles);

	name = obj.name;
}

ObjectHandler::~ObjectHandler()
{
	delete[] vertices;
	delete[] triangles;
}


ObjectHandler& ObjectHandler::operator=(const ObjectHandler& obj)
{
	num_vertices = obj.num_vertices;
	num_triangles = obj.num_triangles;

	InitializeArrays(obj.vertices, obj.triangles);

	name = obj.name;

	return *this;
}

ObjectHandler ObjectHandler::Duplicate()
{
	return ObjectHandler(vertices, num_vertices, triangles, num_triangles,
						 transform, name + "_Copy");
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

void ObjectHandler::InitializeArrays(float* _vertices, int* _triangles)
{
	vertices = new float[num_vertices * 4];
	triangles = new int[num_triangles * 3];

	// We use four for each vertice so that it can have a w component, which is
	// needed for matrix multiplication.
	memcpy(vertices, _vertices, sizeof(float) * num_vertices * 4);
	memcpy(triangles, _triangles, sizeof(int) * num_triangles * 3);
}
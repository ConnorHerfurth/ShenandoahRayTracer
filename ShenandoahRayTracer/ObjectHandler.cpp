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

ObjectHandler::ObjectHandler(std::string file_location)
{
	transform = Transform();
	// Checking if we can load the file
	std::ifstream file(file_location);

	if (!file)
		throw std::invalid_argument("File not found for .obj loading.");
	
	// Reading all the lines into a vector
	std::vector<std::string> lines;
	std::string line;
	
	while (std::getline(file, line))
		lines.push_back(line);

	// Now we use helper methods to individually find vertices, uvs, triangles,
	// and triangle_uvs.

	InitializeVertices(&lines);
	InitializeTriangles(&lines);
	InitializeUVs(&lines);

	name = "Test";
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

void ObjectHandler::InitializeVertices(std::vector<std::string>* lines)
{
	// Unformatted regex:
	// \s*v\s+(-?[0-9]+.[0-9]+)\s+(-?[0-9]+.[0-9]+)\s+(-?[0-9]+.[0-9]+)\s*(-?[0-9]+.[0-9]+)?\s*
	std::regex pattern = std::regex("\\s*v\\s+(-?[0-9]+.[0-9]+)\\s+(-?[0-9]+.[0-9]+)\\s+(-?[0-9]+.[0-9]+)\\s*(-?[0-9]+.[0-9]+)?\\s*");
	std::smatch matches;

	std::vector<float> values; // Vector for loading the vertices

	for (int i = 0; i < lines->size(); i++)
	{
		if (std::regex_match(lines->at(i), matches, pattern))
		{
			values.push_back(std::stof(matches[1]));
			values.push_back(std::stof(matches[2]));
			values.push_back(std::stof(matches[3]));

			if (matches[4] == "")
				values.push_back(1);
			else
				values.push_back(std::stof(matches[4]));
		}
	}

	// Initializing array and copying data.
	num_vertices = values.size() / 4;
	vertices = new float[num_vertices * 4];

	std::copy(values.begin(), values.end(), vertices);
}

void ObjectHandler::InitializeTriangles(std::vector<std::string>* lines)
{
	// This will also match and load quads, but converts them to triangles so
	// it fits in the pipeline.  Face normals will be ignored, as the code
	// doesn't deal with normals.
	
	// Unformatted regex:
	// \s*f\s+([0-9]+)\/?\/?([0-9]+)?\/?([0-9]+)?\s+([0-9]+)\/?\/?([0-9]+)?\/?([0-9]+)?\s+([0-9]+)\/?\/?([0-9]+)?\/?([0-9]+)?
	std::regex pattern = std::regex("\\s*f\\s+([0-9]+)\\/?\\/?([0-9]+)?\\/?([0-9]+)?\\s+([0-9]+)\\/?\\/?([0-9]+)?\\/?([0-9]+)?\\s+([0-9]+)\\/?\\/?([0-9]+)?\\/?([0-9]+)?");
	std::smatch matches;

	std::vector<int> triangle_values;
	std::vector<int> uv_values;

	bool using_uvs = true;

	for (int i = 0; i < lines->size(); i++)
	{
		if (std::regex_match(lines->at(i), matches, pattern))
		{
			// Adding triangle numbers
			triangle_values.push_back(std::stoi(matches[1]) - 1);
			triangle_values.push_back(std::stoi(matches[4]) - 1);
			triangle_values.push_back(std::stoi(matches[7]) - 1);

			// Adding triangle UVs, if they exist.  If they don't, we just
			// assume that they all use the zero uv.
			if (matches[2] != "" && using_uvs)
			{
				uv_values.push_back(std::stoi(matches[2]) - 1);
				uv_values.push_back(std::stoi(matches[5]) - 1);
				uv_values.push_back(std::stoi(matches[8]) - 1);
			}
			else
			{
				using_uvs = false;
			}
		}
	}

	// Initializing arrays and copying values over
	num_triangles = triangle_values.size() / 3;
	triangles = new int[num_triangles * 3];
	triangle_uvs = new int[num_triangles * 3];

	std::copy(triangle_values.begin(), triangle_values.end(), triangles);

	if (using_uvs)
		std::copy(uv_values.begin(), uv_values.end(), triangle_uvs);
	else
	{
		for (int i = 0; i < num_triangles; i++)
			triangle_uvs[i] = 0;
	}
}

void ObjectHandler::InitializeUVs(std::vector<std::string>* lines)
{
	// Unformatted regex:
	// \\s*vt\\s+([0-9]+.[0-9]+)\\s+([0-9]+.[0-9]+)
	std::regex pattern = std::regex("\\s*vt\\s+([0-9]+.[0-9]+)\\s+([0-9]+.[0-9]+)");
	std::smatch matches;

	std::vector<float> values;

	for (int i = 0; i < lines->size(); i++)
	{
		if (std::regex_match(lines->at(i), matches, pattern))
		{
			values.push_back(std::stof(matches[1]));
			values.push_back(std::stof(matches[2]));
		}
	}

	// Initializing array and copying data.
	num_uvs = values.size() / 2;
	uvs = new float[num_uvs * 2];

	std::copy(values.begin(), values.end(), uvs);
}
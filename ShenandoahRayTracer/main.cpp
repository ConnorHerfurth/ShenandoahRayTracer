#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>
#include "ObjectHandler.h"
#include "Device.h"
#include "Camera.h"

int main()
{
	int width = 500;
	int height = 500;

	Camera c = Camera(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(1, 0, 0), width, height, 90, 1);

	float vertices[16] = { 1,10,-1,1,
						  -1,2,-1,1,
						  -1,2,1,1,
	                       1,2,1,1};
	int triangles[6] = { 0,1,2,0,3,2 };
	float uvs[8] = { 0,0,0,63,63,63,63,0};
	int triangle_uvs[6] = { 0,1,2,0,1,3 };

	ObjectHandler oh = ObjectHandler(vertices, 4, uvs, 4, triangles, 2, triangle_uvs, Transform(), "test");

	CPUDevice device = CPUDevice();

	std::vector<ObjectHandler*> objects;
	objects.emplace_back(&oh);

	device.UploadData(&objects);

	int* output = new int[width * height * 3];

	auto start = std::chrono::high_resolution_clock::now();
	device.RenderFrame(c, 1, output);
	auto stop = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;

	std::ofstream file;
	file.open("test.txt", std::ofstream::trunc);

	for (int i = 0; i < width * height * 3; i += 3)
	{
		file << "(" << output[i] << "," << output[i + 1] << "," << output[i + 2] << ")" << std::endl;
	}

	delete[] output;

	return 0;
}
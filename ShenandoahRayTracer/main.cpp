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
	std::cout << c.GetForward().ToString() << std::endl;

	ObjectHandler oh = ObjectHandler("C:\\Users\\Connor Herfurth\\Documents\\MonkeyOnly.obj");
	oh.transform.OffsetOrigin(Vector3(0, -5, 0));

	float* vertices = new float[oh.GetNumVertices() * 4];
	oh.CopyAdjustedVertices(vertices);

	float* uvs = new float[oh.GetNumUVs() * 2];
	oh.CopyUVs(uvs);

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
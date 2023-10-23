#pragma once

#include <vector>
#include <thread>
#include "ObjectHandler.h"
#include "Camera.h"

class Device;
class CPUDevice;

struct Hit;

// A class that encapsulates a specific implementation of the ray tracing
// algorithm, either for different devices (CPU, GPU, Optix) or for specific
// algorithms.
class Device
{
public:
	// Checks whether the device is compatible with the current hardware.
	virtual bool IsDeviceCompatible() = 0;
	
	// Returns true if the device is ready to render the next frame.
	virtual bool IsDeviceReady() = 0;

	// Returns true if the device has finished rendering the current frame.
	virtual bool IsDeviceFinished() = 0;
	
	// Creates multiple threads to render a frame.  Each thread can handle a
	// specific part of the image, such dividing it up into squares or just
	// using one thread.  
	virtual void RenderFrame(Camera c, int max_threads, int* output_location) = 0;

	// Handles the data depending on the device in question.  For CPUs, there
	// might be no need; for GPUs it will have to be uplaoded.  Entirely depends
	// on specific implementation.
	virtual void UploadData(std::vector<ObjectHandler*>* objects) = 0;

protected:
	bool is_ready = false;
	bool is_finished = false;
};

class CPUDevice : public Device
{
public:
	CPUDevice();

	bool IsDeviceCompatible();
	bool IsDeviceReady();
	bool IsDeviceFinished();

	void RenderFrame(Camera c, int max_threads, int* output_location);

	void UploadData(std::vector<ObjectHandler*>* _objects);

private:
	// This CPU Device doesn't copy the data since there's no advantage to it.
	// Instead, we just hold the vector of objects so that we don't duplicate
	// memory.  This is one of the reasons that render handlers are not allowed
	// to update objects until the frame has finished rendering.
	std::vector<ObjectHandler*>* objects;

	// This renders a horizontal section.  It could technically be squares like
	// many engines, but as far as I can tell this offers no benefit other than
	// seeing the image being built, and since the engine doesn't currently
	// display this seems fine.
	void RenderSection(float* origin, float* positions, int num_positions, int* output_location);

	// This implements the Moller-Trumbore algorithm, generally the fastest
	// one that is easy to implement.  Origin and direction are both Vector3
	// array equivalents, while vertices is the vertices that are being tested
	// against.  triangle is the location of the triangle (this function only
	// tests one triangle).  t, u, and v are all output variables used for 
	// detecting the nearest hit.
	void GetRayHit(float* origin, float* direction, float* vertices,
					int* triangle, Hit* output);
};

struct Hit
{
	bool hit = false;
	float t, u, v;
	int triangle_index; // The index of the triangle that was hit.
	ObjectHandler* object = nullptr; // The object that was hit.

	bool IsGreater(Hit h);
};
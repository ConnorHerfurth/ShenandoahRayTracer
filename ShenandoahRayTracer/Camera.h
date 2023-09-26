#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include "Vector.h"

class Camera
{
public:
	Camera();
	Camera(Vector3 _origin, Vector3 _up, Vector3 _right, int _resx, int _resy,
		   float _vertical_fov, float _focal);

	Vector3 GetOrigin();
	Vector3 GetUp();
	Vector3 GetRight();
	Vector3 GetForward();
	int GetResolutionX();
	int GetResolutionY();
	float GetAspectRatio();
	float GetVerticalFOV();
	float GetFocalLength();

	void SetOrigin(Vector3 vec);
	void SetRight(Vector3 vec);
	void SetUp(Vector3 vec);
	void SetResolutionX(int new_x);
	void SetResolutionY(int new_y);
	void SetFocalLength(float new_focal);
	void SetVerticalFOV(float new_fov);

	Vector3 GetPixelRayDirection(int i, int j);
	void GetPixelRayDirection(int i, int j, float* output_location);

private:
	Vector3 origin;  // O
	Vector3 up;      // vv
	Vector3 right;   // uv
	Vector3 forward; // dv
	float vectors[12]; // Used to store the values in such a way that in-place
	                   // methods can take advantage of them without having to
					   // copy them during runtime.
	float temp_vectors[3];

	float* origin_address = &vectors[0];
	float* up_address = &vectors[3];
	float* right_address = &vectors[6];
	float* forward_address = &vectors[9];


	float focal_length; // d
	float aspect_ratio;
	float vertical_fov;
	float width;
	float height;
	float left_distance;   // l
	float right_distance;  // r
	float bottom_distance; // b
	float top_distance;    // t

	int resolution_x; // nx
	int resolution_y; // ny

	void RefreshVectorArray();
	void SetHeightAndWidth();
	void SetFrameDistances();
};
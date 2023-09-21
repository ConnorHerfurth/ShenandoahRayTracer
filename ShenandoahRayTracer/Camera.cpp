#include "Camera.h"

float DegreesToRadians(float degrees)
{
	return degrees * M_PI / 180;
}

Camera::Camera()
{
	origin = Vector3(0, 0, 0);
	up = Vector3(0, 0, 1);
	right = Vector3(1, 0, 0);

	// Forward is normalized since it will be multiplied by focal_length
	forward = Vector3::Normalize(Vector3::Cross(right, up));
	focal_length = 1;

	RefreshVectorArray();

	// These are set to 1 instead of zero since zero can cause division errors.
	resolution_x = 1;
	resolution_y = 1;
	aspect_ratio = resolution_x / resolution_y;

	vertical_fov = 90;
	SetHeightAndWidth();

	SetFrameDistances();
}

Camera::Camera(Vector3 _origin, Vector3 _up, Vector3 _right, int _resx, int _resy,
		   float _vertical_fov, float _focal)
{
	SetOrigin(_origin);
	SetUp(_up);
	SetRight(_right);

	// Forward is normalized since it will be multiplied by focal_length
	forward = Vector3::Normalize(Vector3::Cross(right, up));

	RefreshVectorArray();

	focal_length = _focal;
	resolution_x = _resx;
	resolution_y = _resy;
	aspect_ratio = resolution_x / resolution_y;

	vertical_fov = _vertical_fov;
	SetHeightAndWidth();

	SetFrameDistances();
}


Vector3 Camera::GetOrigin()
{
	return origin.Copy();
}

Vector3 Camera::GetUp()
{
	return up.Copy();
}

Vector3 Camera::GetRight()
{
	return right.Copy();
}

Vector3 Camera::GetForward()
{
	return forward.Copy();
}

int Camera::GetResolutionX()
{
	return resolution_x;
}

int Camera::GetResolutionY()
{
	return resolution_y;
}

float Camera::GetAspectRatio()
{
	return aspect_ratio;
}

float Camera::GetVerticalFOV()
{
	return vertical_fov;
}

float Camera::GetFocalLength()
{
	return focal_length;
}


void Camera::SetOrigin(Vector3 vec)
{
	origin = vec.Copy();
	RefreshVectorArray();
}

// We don't have to copy for these two since normalization already returns a new
// vector.
void Camera::SetRight(Vector3 vec)
{
	right = Vector3::Normalize(vec);

	forward = Vector3::Cross(right, up);

	RefreshVectorArray();
}

void Camera::SetUp(Vector3 vec)
{
	up = Vector3::Normalize(vec);

	forward = Vector3::Cross(right, up);

	RefreshVectorArray();
}

void Camera::SetResolutionX(int new_x)
{
	resolution_x = new_x;
	aspect_ratio = resolution_x / resolution_y;

	SetHeightAndWidth();

	SetFrameDistances();
}

void Camera::SetResolutionY(int new_y)
{
	resolution_y = new_y;
	aspect_ratio = resolution_x / resolution_y;

	SetHeightAndWidth();

	SetFrameDistances();
}

void Camera::SetFocalLength(float new_focal)
{
	focal_length = new_focal;

	SetHeightAndWidth();

	SetFrameDistances();
}

void Camera::SetVerticalFOV(float new_fov)
{
	vertical_fov = new_fov;

	SetHeightAndWidth();

	SetFrameDistances();
}


// Finds the world position of a given pixel (i, j)
Vector3 Camera::GetPixelRayDirection(int i, int j)
{
	float u = left_distance + (right_distance - left_distance) *
		                      (i + 0.5) / resolution_x;
	float v = bottom_distance + (top_distance - bottom_distance) *
								(j + 0.5) / resolution_y;

	return (forward * focal_length) + (right * u) + (up * v);
}

// Same as previous method, but in-place.
void Camera::GetPixelRayDirection(int i, int j, float* output_location)
{
	float u = left_distance + (right_distance - left_distance) *
		(i + 0.5) / resolution_x;
	float v = bottom_distance + (top_distance - bottom_distance) *
		(j + 0.5) / resolution_y;
	
	// In this situation we multiply the vectors that are in the array by their
	// respective values.  This saves allocation time, since we only have to
	// use the temp_vectors variable that is pre-allocated in the constructor.
	Vector3::MultiplyF(forward_address, focal_length, output_location);
	Vector3::MultiplyF(right_address, u, &temp_vectors[0]);
	Vector3::Add(output_location, &temp_vectors[0], output_location);
	Vector3::MultiplyF(up_address, v, &temp_vectors[0]);
	Vector3::Add(output_location, &temp_vectors[0], output_location);
	Vector3::Normalize(output_location);
}


// Puts the values in the origin, up, right, and forward vectors into the array.
// Should be called any time a camera vector is changed.
void Camera::RefreshVectorArray()
{
	origin.Copy(origin_address);
	up.Copy(up_address);
	right.Copy(right_address);
	forward.Copy(forward_address);
}

// Should be called every time the FOV, resolution, or focal length change.
void Camera::SetHeightAndWidth()
{
	height = tan(DegreesToRadians(vertical_fov / 2)) * focal_length;
	width = height * aspect_ratio;
}

// Should be called every time the height or width change.
void Camera::SetFrameDistances()
{
	// These values are used for the algorithm that determines camera points.
	// They represent the maximum distance along the u and v vectors that
	// lie within the camera plane.
	top_distance = height / 2;
	bottom_distance = -top_distance;
	right_distance = width / 2;
	left_distance = -right_distance;
}
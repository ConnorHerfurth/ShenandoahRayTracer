#include "Device.h"

#define EPSILON 0.000001

CPUDevice::CPUDevice()
{
	
}

// This just returns true because we assume that if the code is running, there
// is probably a CPU capable of running this code.
bool CPUDevice::IsDeviceCompatible()
{
	return true;
}

bool CPUDevice::IsDeviceReady()
{
	return is_ready;
}

bool CPUDevice::IsDeviceFinished()
{
	return is_finished;
}


void CPUDevice::RenderFrame(Camera c, int max_threads, int* output_location)
{
	// We don't trust the thread number provided because it could be wrong.
	max_threads = fmin(max_threads, std::thread::hardware_concurrency());

	is_finished = false;

	Vector3 camera_origin = c.GetOrigin();
	// We switch this over so that there's no vector copying at all, which
	// accelerates the process.
	float camera_origin_array[3] = { camera_origin.x, camera_origin.y,
									 camera_origin.z };

	float* camera_points_array = new float[3 * c.GetResolutionX() * c.GetResolutionY()];
	for (int j = 0; j < c.GetResolutionY(); j++)
	{
		for (int i = 0; i < c.GetResolutionX(); i++)
		{
			c.GetPixelRayDirection(i, j,
								   &camera_points_array[(j * c.GetResolutionX() + i) * 3]);
		}
	}


	
	int current_thread_position = 0;
	int pixels_per_thread = c.GetResolutionX() * c.GetResolutionY() / max_threads;
	std::vector<std::thread> threads;
	for (current_thread_position = 0; current_thread_position < max_threads; current_thread_position++)
	{
		threads.emplace_back(std::thread(&CPUDevice::RenderSection, this,
			camera_origin_array,
			&camera_points_array[current_thread_position * pixels_per_thread*3],
			pixels_per_thread,
			&output_location[current_thread_position * pixels_per_thread * 3]));
	}

	for (int i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}

	delete[] camera_points_array;
}

void CPUDevice::RenderSection(float* origin, float* positions, int num_positions, 
	                          int* output_location)
{
	float t, u, v;
	float best_t, best_u, best_v;
	ObjectHandler best_object;
	ObjectHandler current_object;
	for (int i = 0; i < num_positions * 3; i+=3)
	{
		t = DBL_MAX;
		best_t = DBL_MAX;
		for (int o = 0; o < objects->size(); o++)
		{
			current_object = objects->at(o);
			int* triangles = new int[current_object.GetNumTriangles() * 3];
			float* vertices = new float[current_object.GetNumVertices() * 4];

			current_object.CopyTriangles(&triangles[0]);
			current_object.CopyAdjustedVertices(&vertices[0]);

			for (int f = 0; f < current_object.GetNumTriangles() * 3; f += 3)
			{
				bool hit = GetRayHit(origin, &positions[i], &vertices[0],
					                 &triangles[f], &t, &u, &v);
				
				if (t < best_t && hit)
				{
					best_t = t;
					best_u = u;
					best_v = v;
					best_object = current_object;
				}
			}
			
			delete[] triangles;
			delete[] vertices;
		}

		if (best_t < DBL_MAX)
		{
			output_location[i] = best_u * 255;
			output_location[i + 1] = best_v * 255;
			output_location[i + 2] = 0;
		}
		else
		{
			output_location[i] = 0;
			output_location[i + 1] = 0;
			output_location[i + 2] = 0;
		}
	}

}

bool CPUDevice::GetRayHit(float* origin, float* direction, float* vertices,
						  int* triangle, float* t, float* u, float* v)
{
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	Vector3::Subtract(&vertices[triangle[1] * 4], &vertices[triangle[0] * 4], edge1);
	Vector3::Subtract(&vertices[triangle[2] * 4], &vertices[triangle[0] * 4], edge2);

	Vector3::Cross(direction, edge2, pvec);

	det = Vector3::Dot(edge1, pvec);
	
	if (det > -EPSILON && det < EPSILON)
		return false;

	inv_det = 1.0f / det;

	Vector3::Subtract(origin, &vertices[triangle[0] * 4], tvec);

	*u = Vector3::Dot(tvec, pvec) * inv_det;

	if (*u < 0.0 || *u > 1.0)
		return false;

	Vector3::Cross(tvec, edge1, qvec);

	*v = Vector3::Dot(direction, qvec) * inv_det;

	if (*v < 0.0 || *u + *v > 1.0)
		return false;

	*t = Vector3::Dot(edge2, qvec) * inv_det;
	
	return true;
}

void CPUDevice::UploadData(std::vector<ObjectHandler>* _objects)
{
	objects = _objects;
}
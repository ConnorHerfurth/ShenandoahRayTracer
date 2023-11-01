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
	std::cout << "Rendering Now..." << std::endl;
	Hit best_hit;
	Hit current_hit;
	ObjectHandler* current_object;
	for (int i = 0; i < num_positions * 3; i+=3)
	{
		for (int o = 0; o < objects->size(); o++)
		{
			current_object = objects->at(o);
			int* triangles = new int[current_object->GetNumTriangles() * 3];
			float* vertices = new float[current_object->GetNumVertices() * 4];

			current_object->CopyTriangles(&triangles[0]);
			current_object->CopyAdjustedVertices(&vertices[0]);

			for (int f = 0; f < current_object->GetNumTriangles() * 3; f += 3)
			{
				GetRayHit(origin, &positions[i], &vertices[0],
					      &triangles[f], &current_hit);
				
				if (current_hit.IsGreater(best_hit))
				{
					best_hit = current_hit;
					best_hit.object = current_object;
					best_hit.triangle_index = f;
				}
			}
			
			delete[] triangles;
			delete[] vertices;
		}

		if (best_hit.hit)
		{
			// Loading UVs and Triangle UVs
			int* triangle_uvs = new int[best_hit.object->GetNumTriangles() * 3];
			float* uvs = new float[best_hit.object->GetNumUVs() * 2];

			best_hit.object->CopyTriangles(triangle_uvs);
			best_hit.object->CopyUVs(uvs);

			// We find the best triangle by taking the index of the best triangle,
			// and copying the triangle UVs into here.
			int best_triangle_uvs[3];
			memcpy(best_triangle_uvs, &triangle_uvs[best_hit.triangle_index],
				   sizeof(int) * 3);

			float a_uvs[2], b_uvs[2], c_uvs[2];
			memcpy(a_uvs, &uvs[best_triangle_uvs[0] * 2], sizeof(float) * 2);
			memcpy(b_uvs, &uvs[best_triangle_uvs[1] * 2], sizeof(float) * 2);
			memcpy(c_uvs, &uvs[best_triangle_uvs[2] * 2], sizeof(float) * 2);

			// Now we create the u and v vectors within the texture plane, by
			// subtracting the UV coordinates of A-B and A-C
			float ab[2], ac[2];
			Vector2::Subtract(b_uvs, a_uvs, ab);
			Vector2::Subtract(c_uvs, a_uvs, ac);

			// Now that we have these vectors, we can compute the final vector
			// for the texture coordinate
			Vector2::MultiplyF(ab, best_hit.u, ab);
			Vector2::MultiplyF(ac, best_hit.v, ac);

			// Same as writing A + ab(u) + ac(v)
			
			Vector2::Add(&uvs[best_triangle_uvs[0]], ab, ab);
			Vector2::Add(ab, ac, ab);
			
			output_location[i] = abs((int)(ab[0] * 63) % 63);
			output_location[i + 1] = abs((int)(ab[1] * 63) % 63);
			output_location[i + 2] = 0;

			delete[] triangle_uvs;
			delete[] uvs;
		}
		else
		{
			output_location[i] = 0;
			output_location[i + 1] = 0;
			output_location[i + 2] = 0;
		}

		best_hit.hit = false;
	}

}

void CPUDevice::GetRayHit(float* origin, float* direction, float* vertices,
						  int* triangle, Hit* output)
{
	output->hit = false;
	float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	float det, inv_det;

	Vector3::Subtract(&vertices[triangle[1] * 4], &vertices[triangle[0] * 4], edge1);
	Vector3::Subtract(&vertices[triangle[2] * 4], &vertices[triangle[0] * 4], edge2);

	Vector3::Cross(direction, edge2, pvec);

	det = Vector3::Dot(edge1, pvec);
	
	if (det > -EPSILON && det < EPSILON)
		return;

	inv_det = 1.0f / det;

	Vector3::Subtract(origin, &vertices[triangle[0] * 4], tvec);

	output->u = Vector3::Dot(tvec, pvec) * inv_det;

	if (output->u < 0.0 || output->u > 1.0)
		return;

	Vector3::Cross(tvec, edge1, qvec);

	output->v = Vector3::Dot(direction, qvec) * inv_det;

	if (output->v < 0.0 || (double)output->u + (double)output->v > 1.0)
		return;

	output->t = Vector3::Dot(edge2, qvec) * inv_det;
	output->hit = true;
}

void CPUDevice::UploadData(std::vector<ObjectHandler*>* _objects)
{
	objects = _objects;
}


bool Hit::IsGreater(Hit h)
{
	if (hit && !h.hit)
		return true;
	else if (!hit && h.hit)
		return false;
	if (t < h.t)
		return true;
	return false;
}
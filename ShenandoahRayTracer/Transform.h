#pragma once

#include "Matrix.h"
#include "Vector.h"

// Transform is used to provide a simple way for objects to represent their
// world position, rotation, and scale, and to get the composite transformation
// matrix out of it.
class Transform
{
public:
	Transform();
	Transform(Vector3 _origin, Vector3 _angles, Vector3 _scale);

	Vector3 GetOrigin();
	Vector3 GetAngles();
	Vector3 GetScale();

	Matrix GetTranslationMatrix();
	Matrix GetRotationMatrix();
	Matrix GetScaleMatrix();
	Matrix GetCompositeMatrix();

	// Offset methods add the vector to the current one.
	void SetOrigin(Vector3 vec);
	void OffsetOrigin(Vector3 vec);
	void SetAngles(Vector3 vec);
	void OffsetAngles(Vector3 vec);
	void SetScale(Vector3 vec);
	void OffsetScale(Vector3 vec);

private:
	Vector3 origin, angles, scale;
	Matrix translate_matrix, rotate_matrix, scale_matrix;
	Matrix composite_matrix;

	void CreateComposite();
};
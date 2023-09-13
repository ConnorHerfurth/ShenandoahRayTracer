#include "Transform.h"

Transform::Transform()
{
	origin = Vector3(0, 0, 0);
	angles = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);

	translate_matrix = Matrix::GetTranslationMatrix(origin);
	rotate_matrix = Matrix::GetRotationMatrix(angles);
	scale_matrix = Matrix::GetScaleMatrix(scale);

	CreateComposite();
}

Transform::Transform(Vector3 _origin, Vector3 _angles, Vector3 _scale)
{
	SetOrigin(_origin);
	SetAngles(_angles);
	SetScale(_scale);
}


Vector3 Transform::GetOrigin()
{
	return origin.Copy();
}

Vector3 Transform::GetAngles()
{
	return angles.Copy();
}

Vector3 Transform::GetScale()
{
	return scale.Copy();
}


Matrix Transform::GetTranslationMatrix()
{
	return translate_matrix;  // We shouldn't need to copy this since there's a
	                          // copy operator in the matrix class.
}

Matrix Transform::GetRotationMatrix()
{
	return rotate_matrix;
}

Matrix Transform::GetScaleMatrix()
{
	return scale_matrix;
}

Matrix Transform::GetCompositeMatrix()
{
	return composite_matrix;
}


void Transform::SetOrigin(Vector3 vec)
{
	origin = vec.Copy();

	translate_matrix = Matrix::GetTranslationMatrix(origin);

	CreateComposite();
}

void Transform::OffsetOrigin(Vector3 vec)
{
	origin = origin + vec;

	translate_matrix = Matrix::GetTranslationMatrix(origin);

	CreateComposite();
}

void Transform::SetAngles(Vector3 vec)
{
	angles = vec.Copy();
	
	rotate_matrix = Matrix::GetRotationMatrix(origin);

	CreateComposite();
}

void Transform::OffsetAngles(Vector3 vec)
{
	angles = angles + vec;

	rotate_matrix = Matrix::GetRotationMatrix(origin);

	CreateComposite();
}

void Transform::SetScale(Vector3 vec)
{
	scale = vec.Copy();
	
	scale_matrix = Matrix::GetScaleMatrix(scale);

	CreateComposite();
}

void Transform::OffsetScale(Vector3 vec)
{
	scale = scale + vec;

	scale_matrix = Matrix::GetScaleMatrix(scale);

	CreateComposite();
}


void Transform::CreateComposite()
{
	// We use the order rotate, scale, translate so that we don't have to move
	// objects away from the origin.
	composite_matrix = (rotate_matrix * scale_matrix) * translate_matrix;
}
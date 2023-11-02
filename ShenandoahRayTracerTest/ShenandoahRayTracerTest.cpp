#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../ShenandoahRayTracer/Vector.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ShenandoahRayTracerTest
{
	static const float TEST_EPSILON = 0.00001f;

	TEST_CLASS(Vector3Test)
	{
	public:
		
		TEST_METHOD(Vector3DefaultConstructor)
		{
			Vector3 vec = Vector3();
			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);
			Assert::AreEqual(0.0f, vec.z);
		}

		TEST_METHOD(Vector3SpecificConstructor)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Assert::AreEqual(1.0f, vec.x);
			Assert::AreEqual(-1.0f, vec.y);
			Assert::AreEqual(5.12341f, vec.z);
		}

		TEST_METHOD(Vector3ArrayConstructor)
		{
			float values[3] = { 1, -1, 5.12341 };
			Vector3 vec = Vector3(values);
			Assert::AreEqual(1.0f, vec.x);
			Assert::AreEqual(-1.0f, vec.y);
			Assert::AreEqual(5.12341f, vec.z);
		}

		TEST_METHOD(Vector3Copy)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = vec1.Copy();
			vec1.x = 4; // Changing it to ensure they are
					    // independent.
			Assert::AreEqual(1.0f, vec2.x);
			Assert::AreEqual(-1.0f, vec2.y);
			Assert::AreEqual(5.12341f, vec2.z);
		}

		TEST_METHOD(Vector3ArrayCopy)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			float values[3];
			vec.Copy(values);
			Assert::AreEqual(1.0f, values[0]);
			Assert::AreEqual(-1.0f, values[1]);
			Assert::AreEqual(5.12341f, values[2]);
		}

		TEST_METHOD(Vector3Equals)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(1, -1, 5.12341);
			Vector3 vec3 = Vector3(4, -1, 5.12341);

			Assert::AreEqual(true, vec1.Equals(vec2, TEST_EPSILON));
			Assert::AreEqual(false, vec1.Equals(vec3, TEST_EPSILON));
		}

		TEST_METHOD(Vector3EqualsArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 1, -1, 5.12341 };
			float vec3[3] = { 4, -1, 5.12341 };

			Assert::AreEqual(true, Vector3::Equals(vec1, vec2, TEST_EPSILON));
			Assert::AreEqual(false, Vector3::Equals(vec1, vec3, TEST_EPSILON));
		}

		TEST_METHOD(Vector3GetMagnitude)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Assert::AreEqual(vec.GetMagnitude(), 5.31500988f);
		}

		TEST_METHOD(Vector3GetMagnitudeArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			Assert::AreEqual(Vector3::GetMagnitude(vec), 5.31500988f);
		}

		TEST_METHOD(Vector3AddVector)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Vector3 expected = Vector3(5, -1, 9.34341);
			Assert::AreEqual(true, expected.Equals(vec1 + vec2, TEST_EPSILON));
		}

		TEST_METHOD(Vector3AddFloat)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Vector3 expected = Vector3(5, 3, 9.12341);
			Assert::AreEqual(true, expected.Equals(vec + 4, TEST_EPSILON));
		}

		TEST_METHOD(Vector3SubVector)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Vector3 expected = Vector3(-3, -1, 0.90341);
			Assert::AreEqual(true, expected.Equals(vec1 - vec2, TEST_EPSILON));
		}

		TEST_METHOD(Vector3SubFloat)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Vector3 expected = Vector3(-3, -5, 1.12341);
			Assert::AreEqual(true, expected.Equals(vec - 4, TEST_EPSILON));
		}

		TEST_METHOD(Vector3MultFloat)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Vector3 expected = Vector3(4, -4, 20.49364);
			Assert::AreEqual(true, expected.Equals(vec * 4, TEST_EPSILON));
		}

		TEST_METHOD(Vector3DivFloat)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Vector3 expected = Vector3(0.25, -0.25, 1.2808525);
			Assert::AreEqual(true, expected.Equals(vec / 4, TEST_EPSILON));
		}

		TEST_METHOD(Vector3GetAngle)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Assert::AreEqual(true, abs(Vector3::GetAngle(vec1, vec2) - 0.593405f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3GetAngleArrays)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			Assert::AreEqual(true, abs(Vector3::GetAngle(vec1, vec2) - 0.593405f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3GetDistance)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Assert::AreEqual(true, abs(Vector3::GetDistance(vec1, vec2) - 3.288792f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3GetDistanceArrays)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			Assert::AreEqual(true, abs(Vector3::GetDistance(vec1, vec2) - 3.288792f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3Dot)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Assert::AreEqual(true, abs(Vector3::Dot(vec1, vec2) - 25.6207902f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3DotArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			Assert::AreEqual(true, abs(Vector3::Dot(vec1, vec2) - 25.6207902f) < TEST_EPSILON);
		}

		TEST_METHOD(Vector3Cross)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Vector3 expected = Vector3(-4.22, 16.27364, 4);
			Assert::AreEqual(true, expected.Equals(Vector3::Cross(vec1, vec2), TEST_EPSILON));
		}

		TEST_METHOD(Vector3CrossArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			float output[3];
			Vector3::Cross(vec1, vec2, output);
			float expected[3] = { -4.22, 16.27364, 4 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3Normalize)
		{
			Vector3 vec = Vector3(1, -1, 5.12341);
			Vector3 expected = Vector3(0.188146f, -0.188146, 0.96395f);
			Assert::AreEqual(true, expected.Equals(Vector3::Normalize(vec), TEST_EPSILON));
		}

		TEST_METHOD(Vector3NormalizeArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			float output[3];
			Vector3::Normalize(vec, output);
			float expected[3] = { 0.188146f, -0.188146, 0.96395f };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3Project)
		{
			Vector3 vec1 = Vector3(1, -1, 5.12341);
			Vector3 vec2 = Vector3(4, 0, 4.22);
			Vector3 expected = Vector3(3.031292, 0, 3.1980139);
			Assert::AreEqual(true, expected.Equals(Vector3::Project(vec2, vec1), TEST_EPSILON));
		}

		TEST_METHOD(Vector3ProjectArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			float output[3];
			Vector3::Project(vec2, vec1, output);
			float expected[3] = { 3.031292, 0, 3.1980139 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3AddArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			float output[3];

			Vector3::Add(vec1, vec2, output);
			float expected[3] = { 5, -1, 9.34341 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}
		
		TEST_METHOD(Vector3AddFloatArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			float output[3];

			Vector3::AddF(vec, 4, output);
			float expected[3] = { 5, 3, 9.12341 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3SubArray)
		{
			float vec1[3] = { 1, -1, 5.12341 };
			float vec2[3] = { 4, 0, 4.22 };
			float output[3];

			Vector3::Subtract(vec1, vec2, output);
			float expected[3] = { -3, -1, 0.90341 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3SubFloatArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			float output[3];

			Vector3::SubtractF(vec, 4, output);
			float expected[3] = { -3, -5, 1.12341 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3MultFloatArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			float output[3];

			Vector3::MultiplyF(vec, 4, output);
			float expected[3] = { 4, -4, 20.49364 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}

		TEST_METHOD(Vector3DivideFloatArray)
		{
			float vec[3] = { 1, -1, 5.12341 };
			float output[3];

			Vector3::DivideF(vec, 4, output);
			float expected[3] = { 0.25, -0.25, 1.2808525 };
			Assert::AreEqual(true, Vector3::Equals(expected, output, TEST_EPSILON));
		}
	};
}

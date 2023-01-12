#pragma once
#include "ColisionPrimitive.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Collision
{
public:
	/// <summary>
	/// ÆÌ½è»è
	/// </summary>
	/// <param name="sphereA">A</param>
	/// <param name="sphereB">B</param>
	/// <param name="intersection">ð_</param>
	/// <param name="exclusion">rËxNg</param>
	/// <returns></returns>
	static bool CheckSphereToSphere(Sphere& sphereA, Sphere& sphereB, Mathematics::Vector4* intersection = nullptr, Mathematics::Vector4* exclusion = nullptr);

	/// <summary>
	/// OBBÆOBBÌ½è»è(QÆnµ)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox& obb1, BoundingBox& obb2);

	/// <summary>
	/// OBBÆOBBÌ½è»è(|C^nµ)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox* obb1, BoundingBox* obb2);
};


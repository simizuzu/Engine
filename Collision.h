#pragma once
#include "ColisionPrimitive.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

class Collision
{
public:
	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球A</param>
	/// <param name="sphereB">球B</param>
	/// <param name="intersection">交点</param>
	/// <param name="exclusion">排斥ベクトル</param>
	/// <returns></returns>
	static bool CheckSphereToSphere(Sphere& sphereA, Sphere& sphereB, Mathematics::Vector4* intersection = nullptr, Mathematics::Vector4* exclusion = nullptr);

	/// <summary>
	/// OBBとOBBの当たり判定(参照渡し)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox& obb1, BoundingBox& obb2);

	/// <summary>
	/// OBBとOBBの当たり判定(ポインタ渡し)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox* obb1, BoundingBox* obb2);
};


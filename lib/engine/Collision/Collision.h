#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "CollisionPrimitive.h"

class Collision
{
public:
	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点（平面上の最近接点）</param>
	/// <returns交差しているか否か></returns>
	static bool CheckSpere2Plane(const Sphere& sphere, const Plane& plane, MyMath::Vector4* inter = nullptr);

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


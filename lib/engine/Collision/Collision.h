#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "lib/engine/Collision/CollisionPrimitive.h"

class Collision
{
public:

	/// <summary>
	/// OBB��OBB�̓����蔻��(�Q�Ɠn��)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox& obb1, BoundingBox& obb2);

	/// <summary>
	/// OBB��OBB�̓����蔻��(�|�C���^�n��)
	/// </summary>
	/// <param name="obb1">OBB1</param>
	/// <param name="obb2">OBB2</param>
	/// <returns></returns>
	static bool CheckOBBToOBB(BoundingBox* obb1, BoundingBox* obb2);
};


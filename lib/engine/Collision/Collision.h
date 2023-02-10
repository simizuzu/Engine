#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "CollisionPrimitive.h"

class Collision
{
public:
	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_�i���ʏ�̍ŋߐړ_�j</param>
	/// <returns�������Ă��邩�ۂ�></returns>
	static bool CheckSpere2Plane(const Sphere& sphere, const Plane& plane, Mathematics::Vector4* inter = nullptr);

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


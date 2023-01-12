#pragma once
#include "Vector3.h"

#include <array>
class BaseCollision
{
public:
	/// <summary>
	/// ���Ƌ��̓����蔻��
	/// </summary>
	bool CheckSphereToSphere();

	
};

struct AABB
{
	// ���S���W
	Mathematics::Vector3 center;
	// �T�C�Y
	Mathematics::Vector3 size;
};

struct SPHERE
{
	// ���S���W
	Mathematics::Vector3 center;
	// ���a
	float radius;
};

class BoundingBox
{
	/// <summary>
	/// AABB��AABB�̓����蔻��
	/// </summary>
	/// <param name="aabb1">1�ڂ�AABB</param>
	/// <param name="aabb2">2�ڂ�AABB</param>
	/// <returns>true</returns>
	bool CheckAABBToAABB(AABB& aabb1, AABB& aabb2);

	/// <summary>
	/// AABB�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="aabb1">1�ڂ�AABB</param>
	/// <param name="aabb2">��</param>
	/// <returns>false</returns>
	bool CheckAABBToSphere(AABB& aabb,SPHERE& sphere);
};
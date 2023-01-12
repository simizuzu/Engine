#pragma once
#include "Vector3.h"

#include <array>
class BaseCollision
{
public:
	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	bool CheckSphereToSphere();

	
};

struct AABB
{
	// 中心座標
	Mathematics::Vector3 center;
	// サイズ
	Mathematics::Vector3 size;
};

struct SPHERE
{
	// 中心座標
	Mathematics::Vector3 center;
	// 半径
	float radius;
};

class BoundingBox
{
	/// <summary>
	/// AABBとAABBの当たり判定
	/// </summary>
	/// <param name="aabb1">1つ目のAABB</param>
	/// <param name="aabb2">2つ目のAABB</param>
	/// <returns>true</returns>
	bool CheckAABBToAABB(AABB& aabb1, AABB& aabb2);

	/// <summary>
	/// AABBと球の当たり判定
	/// </summary>
	/// <param name="aabb1">1つ目のAABB</param>
	/// <param name="aabb2">球</param>
	/// <returns>false</returns>
	bool CheckAABBToSphere(AABB& aabb,SPHERE& sphere);
};
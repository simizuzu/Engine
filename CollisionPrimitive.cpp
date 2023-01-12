#include "CollisionPrimitive.h"

const uint32_t BaseCollision::GetCollisionAttribute()
{
	return collisionAttribute_;
}

void BaseCollision::SetCollisionAttribute(uint32_t collisionAttribute)
{
	collisionAttribute_ = collisionAttribute;
}

const uint32_t BaseCollision::GetCollisionMask()
{
	return collisionMask_;
}

void BaseCollision::SetCollisionMask(uint32_t collisionMask)
{
	collisionMask_ = collisionMask;
}

void BaseCollision::SetCollsionName(std::string name)
{
	collsionName_ = name;
}

std::string BaseCollision::GetCollsionName()
{
	return collsionName_;
}

void BaseCollision::SetOppCollsionName(std::string name)
{
	for (size_t i = 0; i < name.size(); i++)
	{
		opponentCollsionName_[i] = name[i];
	}
}

std::string BaseCollision::GetOppCollsionName()
{
	return opponentCollsionName_;
}

const Mathematics::Vector3 BoundingBox::GetDirectVec(uint16_t element)
{
	return directionVec[element];
}

const float BoundingBox::GetLength(uint16_t element)
{
	return length[element];
}

const Mathematics::Vector3 BoundingBox::GetCenter()
{
	return center;
}

bool BoundingBox::CheckAABBToAABB(AABB& aabb1, AABB& aabb2)
{
	std::array<Mathematics::Vector3, 2> min_;
	min_[0] = { aabb1.center.x - aabb1.size.x, aabb1.center.y - aabb1.size.y ,aabb1.center.z - aabb1.size.z };
	min_[1] = { aabb2.center.x - aabb2.size.x, aabb2.center.y - aabb2.size.y ,aabb2.center.z - aabb2.size.z };
	std::array<Mathematics::Vector3, 2> max_;
	max_[0] = { aabb1.center.x + aabb1.size.x, aabb1.center.y + aabb1.size.y ,aabb1.center.z + aabb1.size.z };
	max_[1] = { aabb2.center.x + aabb2.size.x, aabb2.center.y + aabb2.size.y ,aabb2.center.z + aabb2.size.z };

	if (min_[0].x > max_[1].x || max_[0].x < min_[1].x ||
		min_[0].y > max_[1].y || max_[0].y < min_[1].y ||
		min_[0].z > max_[1].z || max_[0].z < min_[1].z)
	{
		return false;
	}

	return true;
}

bool BoundingBox::CheckAABBToSphere(AABB& aabb, SPHERE& sphere)
{
	std::array<Mathematics::Vector3, 8> vex;

	vex[0] = { aabb.center.x - aabb.size.x, aabb.center.y - aabb.size.y ,aabb.center.z - aabb.size.z };
	vex[1] = { aabb.center.x - aabb.size.x, aabb.center.y - aabb.size.y ,aabb.center.z + aabb.size.z };
	vex[2] = { aabb.center.x + aabb.size.x, aabb.center.y - aabb.size.y ,aabb.center.z - aabb.size.z };
	vex[3] = { aabb.center.x + aabb.size.x, aabb.center.y - aabb.size.y ,aabb.center.z + aabb.size.z };

	vex[4] = { aabb.center.x - aabb.size.x, aabb.center.y + aabb.size.y ,aabb.center.z - aabb.size.z };
	vex[5] = { aabb.center.x - aabb.size.x, aabb.center.y + aabb.size.y ,aabb.center.z + aabb.size.z };
	vex[6] = { aabb.center.x + aabb.size.x, aabb.center.y + aabb.size.y ,aabb.center.z - aabb.size.z };
	vex[7] = { aabb.center.x + aabb.size.x, aabb.center.y + aabb.size.y ,aabb.center.z + aabb.size.z };

	for (Mathematics::Vector3 v : vex)
	{
		float ren = (fabs(v.x - sphere.center.x)) * 2 + (fabs(v.y - sphere.center.y)) * 2 + (fabs(v.z - sphere.center.z)) * 2;

		if (fabs(ren) < sphere.radius * 2)
		{
			return true;
		}

	}

	return false;
}

void BoundingBox::CreateOBB(std::vector<VertexPosNormalUv> vertex, Object3d& transform)
{
	// 回転
	Mathematics::Matrix4 matRot;

	// 最大値、最小値の初期化設定
	Mathematics::Vector3 max = Mathematics::Vector3(-10000.0f, -10000.0f, -10000.0f);
	Mathematics::Vector3 min = Mathematics::Vector3(10000.0f, 10000.0f, 10000.0f);

	// メッシュの頂点データを取得
	std::vector<VertexPosNormalUv> vertex_ = vertex;
	// 最大値、最小値を取得
	for (size_t i = 0; i < vertex_.size(); i++)
	{
		Mathematics::Vector3 pos = vertex_[i].pos;
		if (pos.x < min.x) { min.x = pos.x; }
		if (pos.x > min.x) { min.x = pos.x; }
		if (pos.y < min.y) { min.y = pos.y; }
		if (pos.y > min.y) { min.y = pos.y; }
		if (pos.z < min.z) { min.z = pos.z; }
		if (pos.z > min.z) { min.z = pos.z; }
	}

	// 中心点座標の取得
	center = transform.position = { 0,0,0 };

	// 方向ベクトルを取得
	matRot = MyMathUtility::MakeRotation(transform.rotation);
	directionVec[0] = { matRot.m[0][0], matRot.m[0][1],matRot.m[0][2] };
	directionVec[1] = { matRot.m[1][0], matRot.m[1][1],matRot.m[1][2] };
	directionVec[2] = { matRot.m[2][0], matRot.m[2][1],matRot.m[2][2] };

	// 長さを取得
	length[0] = fabs(max.x - min.x) * 0.5f;
	length[1] = fabs(max.y - min.y) * 0.5f;
	length[2] = fabs(max.z - min.z) * 0.5f;

	length[0] *= transform.scale.x;
	length[1] *= transform.scale.y;
	length[2] *= transform.scale.z;
}

void BoundingBox::UpdateOBB(Object3d& transform)
{
	Mathematics::Matrix4 matRot;

	// 中心座標を取得
	center = Mathematics::GetWorldPosition(transform);

	// 方向ベクトルを取得
	matRot = MyMathUtility::MakeRotation(transform.rotation);
	directionVec[0] = { matRot.m[0][0],matRot.m[0][1],matRot.m[0][2] };
	directionVec[1] = { matRot.m[1][0],matRot.m[1][1],matRot.m[1][2] };
	directionVec[2] = { matRot.m[2][0],matRot.m[2][1],matRot.m[2][2] };
}
#include "ColisionPrimitive.h"

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

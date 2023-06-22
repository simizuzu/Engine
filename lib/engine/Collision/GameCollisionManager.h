#pragma once
#include <list>

#include "Collision.h"
#include "CollisionPrimitive.h"

class GameCollisionManager
{
private:
	std::list<BoundingBox*> colliders_;

public:
	void ColliderSet(BoundingBox* collider);

	void ListClear();

	void CheckCollisions();

private:
	void CheckOBB2OBB(BoundingBox* colliderA, BoundingBox* colliderB);
};


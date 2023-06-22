#include "GameCollisionManager.h"

void GameCollisionManager::ColliderSet(BoundingBox* collider)
{
	colliders_.push_back(collider);
}

void GameCollisionManager::ListClear()
{
	if (!colliders_.empty())
	{
		colliders_.clear();
	}
}

void GameCollisionManager::CheckCollisions()
{
	std::list<BoundingBox*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA)
	{
		BoundingBox* colliderA = *itrA;

		std::list<BoundingBox*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB)
		{
			BoundingBox* colliderB = *itrB;

			//ペアの当たり判定
			CheckOBB2OBB(colliderA, colliderB);
		}
	}
}

void GameCollisionManager::CheckOBB2OBB(BoundingBox* colliderA, BoundingBox* colliderB)
{
	if (colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask() ||
		colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()){}
	else
	{
		return;
	}

	if (Collision::CheckOBBToOBB(colliderA, colliderB))
	{
		colliderA->SetOppCollsionName(colliderB->GetCollsionName());
		colliderB->SetOppCollsionName(colliderA->GetCollsionName());

		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}

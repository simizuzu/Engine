#pragma once
#include "Object3d.h"
#include "ObjModel.h"
#include "WorldTransform.h"

class PlayerBullet
{
public:
	void Initialize(ObjModel* model,Object3d* obj, const MyMath::Vector3& position);

	void Update(Camera* camera);

	void Draw();

private:
	ObjModel* bulletModel_ = nullptr;
	Object3d* bulletObj_ = nullptr;

	WorldTransform bulletTrans_;
};


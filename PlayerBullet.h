#pragma once
#include"Object3d.h"
#include"ObjModel.h"

class PlayerBullet
{
public:
	void Initialize(ObjModel* model);

	void Update();

	void Draw();

private:
	std::unique_ptr<ObjModel> bulletModel_;
	std::unique_ptr<Object3d> bulletObj_;
};


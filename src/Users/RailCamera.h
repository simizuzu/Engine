#pragma once
#include <memory>
#include "DirectX12Math.h"
#include "WorldTransform.h"
#include "Camera.h"

class RailCamera
{
public:
	void Initailize(Camera* camera);

	void Update();

private:
	WorldTransform worldTransform_;
	std::unique_ptr<Camera> camera_;
};


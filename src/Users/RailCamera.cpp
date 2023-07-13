#include "RailCamera.h"

void RailCamera::Initailize(Camera* camera)
{
	worldTransform_.translation_ = { 0.0f,0.0f,-200.0f };
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };
	worldTransform_.rotation_ = { 0.0f,0.0f,0.0f };

	camera_.reset(camera);
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
}

void RailCamera::Update()
{
	worldTransform_.translation_.z += 0.5f;
	worldTransform_.Update(camera_.get());
	camera_->matView_ = MyMathUtility::MakeInverse(worldTransform_.matWorld);
}

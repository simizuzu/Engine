#include "GameCamera.h"

void GameCamera::Initialize()
{
	input_ = Input::GetInstace();

	thirdPersonCamera_ = std::make_unique<Camera>();
	thirdPersonCamera_->SetFarZ(40000.0f);
	thirdPersonCamera_->Initialize();
	thirdPersonTransform_.position = { 0.0f,4000.0f,-5000.0f };
}

void GameCamera::Update()
{
	Mathematics::Vector3 move(0, 0, 0);
	Mathematics::Vector3 front;
	Mathematics::Vector3 frontVec;
	Mathematics::Vector3 frontNormVec;

	float rotationSpeed = 0.01f;

	thirdPersonTransform_.rotation.y += rotationSpeed * input_->GetLeftStickVec().x;
	thirdPersonTransform_.rotation.x += rotationSpeed * input_->GetLeftStickVec().y;

	thirdPersonTransform_.rotation.y += rotationSpeed * input_->GetKeyTime()
}

Camera* GameCamera::GetThirdPersonCamera()
{
	return nullptr;
}

float GameCamera::GetSpeed()
{
	return 0.0f;
}

Object3d* GameCamera::GetFirstPersonTransform()
{
	return nullptr;
}

Mathematics::Vector3 GameCamera::GetWorldPosition()
{
	return Mathematics::Vector3();
}

void GameCamera::SetPos(Mathematics::Vector3 pos)
{
}

Mathematics::Vector3 GameCamera::GetFront()
{
	return Mathematics::Vector3();
}

void GameCamera::Move()
{
}

void GameCamera::ThirdPersonUpdate(Mathematics::Vector3& move, Mathematics::Vector3& rot)
{
}

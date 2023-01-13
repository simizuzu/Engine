#include "Goal.h"

void Goal::Initialize()
{
	worldTransform_ = std::make_unique<Object3d>();
	worldTransform_->Initialize();

	worldTransform_->position = { 18.0f,-3.0f,-30.0f };
	worldTransform_->scale = { 4.0f,4.0f,4.0f };
	worldTransform_->rotation = { 0.0f,150.0f * MyMathUtility::degree2Radius, 0.0f };

	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("goal"));
	worldTransform_ = std::make_unique<Object3d>();
	worldTransform_->Initialize();
	worldTransform_->SetModel(model_.get());
}

void Goal::Draw(Camera* camera)
{
	worldTransform_->Update(camera);
	worldTransform_->Draw();
}
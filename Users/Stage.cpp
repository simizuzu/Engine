#include "Stage.h"

void Stage::Initialize()
{
	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("stage"));
	WorldTransform_.reset(Object3d::Create());
	WorldTransform_->Initialize();
	WorldTransform_->SetModel(model_.get());

	WorldTransform_->SetPosition({ 375.25f,-3.0f,375.25f });
	WorldTransform_->SetScale({ 12.0f,1.0f,12.0f });
}

void Stage::Update(Camera* camera)
{
	WorldTransform_->Update(camera);
}

void Stage::Draw()
{
	WorldTransform_->Draw();
}

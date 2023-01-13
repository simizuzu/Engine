#include "skydome.h"

void skydome::Initialize()
{
	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("skydome"));
	transform_ = std::make_unique<Object3d>();
	transform_.reset(Object3d::Create());
	transform_->SetModel(model_.get());
	// ƒXƒP[ƒ‹‚ðÝ’è
	transform_->SetScale({ 10000.0f,10000.0f,10000.0f });
}

void skydome::Update(Camera* camera)
{
	transform_->Update(camera);
}

void skydome::Draw()
{
	transform_->Draw();
}

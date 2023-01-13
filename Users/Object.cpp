#include "Object.h"

void Object::Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, float radius, Model* model)
{
	worldTransform_ = std::make_unique<Object3d>();

	worldTransform_->position = pos;
	worldTransform_->scale = { 1.0f,1.0f,1.0f };
	worldTransform_->rotation = rot;

	worldTransform_->Initialize();

	model_ = model;

	collider_.center = worldTransform_->position;
	collider_.radius = radius;
}

void Object::Update()
{

}

void Object::Draw(Camera* camera)
{
	worldTransform_->Update(camera);
	worldTransform_->Draw();
}

Sphere& Object::GetCollider()
{
	return collider_;
}

bool Object::GetIsDeath()
{
	return IsDeath;
}

void Object::OnCollision()
{
	IsDeath = true;
}
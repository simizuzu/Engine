#include "Door.h"

door::door()
{
}

door::~door()
{
}

void door::Initialize(Mathematics::Vector3 trans, Mathematics::Vector3 Rot)
{
	door1worldTransform_.reset(Object3d::Create());
	door2worldTransform_.reset(Object3d::Create());
	door3worldTransform_.reset(Object3d::Create());

	door1model_ = std::make_unique<Model>();
	door2model_ = std::make_unique<Model>();
	door3model_ = std::make_unique<Model>();

	door1model_.reset(Model::LoadFromObj("door"));
	door2model_.reset(Model::LoadFromObj("door2"));
	door3model_.reset(Model::LoadFromObj("door3"));

	door1worldTransform_->SetModel(door1model_.get());
	door2worldTransform_->SetModel(door2model_.get());
	door3worldTransform_->SetModel(door3model_.get());

	input_ = Input::GetInstace();

	door1worldTransform_->SetPosition(Mathematics::Vector3(trans.x, trans.y, trans.z + 0.3f));
	door2worldTransform_->SetPosition(trans);
	door3worldTransform_->SetPosition(trans);

	door1worldTransform_->SetScale({ 10.0f,10.0f,1.0f });
	door2worldTransform_->SetScale({ 10.0f,10.0f,1.0f });
	door3worldTransform_->SetScale({ 10.0f,10.0f,1.0f });

	door1worldTransform_->SetRotation(Rot);
	door2worldTransform_->SetRotation(Rot);
	door3worldTransform_->SetRotation(Rot);
}

void door::Mash(Mathematics::Vector3 vector)
{
	if (input_->TriggerPushKey(DIK_SPACE))
	{
		mashNum_++;
		door2worldTransform_->position-= vector;
		door3worldTransform_->position += vector;
	}
	if (mashNum_ > 10)
	{
		mashNum_ = 0;
		mashFlag_ = true;
	}
}

void door::Update(Mathematics::Vector3 vector)
{
	Mash(vector);
}

void door::Draw(Camera* camera)
{
	door1worldTransform_->Update(camera);
	door2worldTransform_->Update(camera);
	door3worldTransform_->Update(camera);

	door3worldTransform_->Draw();
	door3worldTransform_->Draw();
	door3worldTransform_->Draw();
}

bool door::GetMashFlag()
{
	return mashFlag_;
}

UINT door::GetMashNum()
{
	return mashNum_;
}

void door::Reset(Mathematics::Vector3 trans)
{
	mashFlag_ = false;
	door1worldTransform_->position = Mathematics::Vector3(trans.x, trans.y, trans.z + 0.3f);
	door2worldTransform_->position = trans;
	door3worldTransform_->position = trans;
}
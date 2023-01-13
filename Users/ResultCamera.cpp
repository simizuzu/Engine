#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(Object3d* worldTransform)
{
	worldTransform_.reset(Object3d::Create());
	worldTransform_->parent = worldTransform;

	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_->position = {2.0f,-2.0f,11.5f};
	worldTransform_->rotation = { 0.0,250.0f * MyMathUtility::degree2Radius,0.0f };

	viewProjection_ = new Camera();
	viewProjection_->SetFarZ(12000.0f);
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize();
}

void ResultCamera::Update()
{

	Mathematics::MakeWorldMatrix4(*worldTransform_);

	viewProjection_->eye_ = Mathematics::GetWorldPosition(*worldTransform_);
	//���[���h�O���x�N�g��
	Mathematics::Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = Mathematics::Vec3Mat4Mul(forward, worldTransform_->matWorld);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_->target_ = viewProjection_->eye_ + forward;
	//���[���h����x�N�g��
	Mathematics::Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_->up_ = Mathematics::Vec3Mat4Mul(up, worldTransform_->matWorld);
}

void ResultCamera::Draw() {}

Camera* ResultCamera::GetViewProjection()
{
	return viewProjection_;
}

Object3d* ResultCamera::GetWorldTransformPtr()
{
	return worldTransform_.get();
}
void ResultCamera::addTranslation(Mathematics::Vector3 translation)
{
	worldTransform_->position += translation;
}
void ResultCamera::addRot(Mathematics::Vector3 rot)
{
	worldTransform_->rotation += rot;
}
void ResultCamera::setTranslation(Mathematics::Vector3 translation)
{
	worldTransform_->position = translation;
}
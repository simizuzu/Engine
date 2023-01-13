#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(Transform* worldTransform)
{
	worldTransform_.parent = worldTransform;

	//���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation = {2.0f,-2.0f,11.5f};
	worldTransform_.rotation = { 0.0,250.0f * EngineMathF::Deg2Rad,0.0f };

	viewProjection_ = std::make_unique<Camera>();
	viewProjection_->SetFar(12000.0f);
	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_->Initialize(UpdateProjMatrixFunc_Perspective);
}

void ResultCamera::Update()
{

	worldTransform_.MakeWorldMatrix();

	viewProjection_->eye = EngineMathF::GetWorldPosition(worldTransform_);
	//���[���h�O���x�N�g��
	EngineMathF::Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = EngineMathF::Vec3Mat4Mul(forward, worldTransform_.matWorld);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_->target = viewProjection_->eye + forward;
	//���[���h����x�N�g��
	EngineMathF::Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_->up = EngineMathF::Vec3Mat4Mul(up, worldTransform_.matWorld);
}

void ResultCamera::Draw() {}

Camera* ResultCamera::GetViewProjection()
{
	return viewProjection_.get();
}

Transform* ResultCamera::GetWorldTransformPtr()
{
	return &worldTransform_;
}
void ResultCamera::addTranslation(EngineMathF::Vector3 translation)
{
	worldTransform_.translation += translation;
}
void ResultCamera::addRot(EngineMathF::Vector3 rot)
{
	worldTransform_.rotation += rot;
}
void ResultCamera::setTranslation(EngineMathF::Vector3 translation)
{
	worldTransform_.translation = translation;
}
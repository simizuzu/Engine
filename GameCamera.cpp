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

	// �R���g���[���[����
	thirdPersonTransform_.rotation.y += rotationSpeed * input_->GetLeftStickVec().x;
	thirdPersonTransform_.rotation.x += rotationSpeed * input_->GetLeftStickVec().y;

	// �L�[�{�[�h����
	thirdPersonTransform_.rotation.y += rotationSpeed * input_->GetKeyTime(DIK_D) / 254.0f;
	thirdPersonTransform_.rotation.y += rotationSpeed * -input_->GetKeyTime(DIK_A) / 254.0f;
	thirdPersonTransform_.rotation.x += rotationSpeed * input_->GetKeyTime(DIK_W) / 254.0f;
	thirdPersonTransform_.rotation.x += rotationSpeed * -input_->GetKeyTime(DIK_S) / 254.0f;

	front.x = thirdPersonTransform_.position.x + cosf(thirdPersonTransform_.rotation.y - MyMathUtility::PIHalf);
	front.y = thirdPersonTransform_.position.y + cosf(thirdPersonTransform_.rotation.x - MyMathUtility::PIHalf);
	front.z = thirdPersonTransform_.position.z - sinf(thirdPersonTransform_.rotation.y - MyMathUtility::PIHalf);

	frontVec = front - thirdPersonTransform_.position;
	frontNormVec = frontVec.normalize();
	front_ = frontNormVec;
	Move();
	moveSpeed_ = speed_ * frontNormVec;
	ThirdPersonUpdate(moveSpeed_, rotSpeed_);
}

Camera* GameCamera::GetThirdPersonCamera()
{
	return thirdPersonCamera_.get();
}

float GameCamera::GetSpeed()
{
	return speed_;
}

Mathematics::Vector3 GameCamera::GetWorldPosition()
{
	return Mathematics::GetWorldPosition(thirdPersonTransform_);
}

void GameCamera::SetPos(Mathematics::Vector3 pos)
{
	thirdPersonTransform_.position = pos;
	thirdPersonTransform_.rotation = { 0.0f,0.0f,0.0f };
	speed_ = minSpeed_;
	acceleration_ = 0.0f;
}

Mathematics::Vector3 GameCamera::GetFront()
{
	return front_;
}

void GameCamera::Move()
{
	//�A�N�Z��
	if (input_->PushButton(RT) || input_->PushButton(RT) || input_->PushKey(DIK_E))
	{
		acceleration_ += accelerationSpeed_;
		acceleration_ = MyMathUtility::Clamp(acceleration_, 0.0f, 1.57f);
		speed_ = minSpeed_ + maxSpeed_ * MyMathUtility::Sin(acceleration_);
		speed_ = MyMathUtility::Clamp(speed_, minSpeed_, maxSpeed_);
	}

	//�u���[�L
	if (input_->PushButton(LT) || input_->PushButton(RT) || input_->PushKey(DIK_Q))
	{
		acceleration_ -= accelerationSpeed_;
		acceleration_ = MyMathUtility::Clamp(acceleration_, 0.0f, 1.57f);
		speed_ = minSpeed_ + maxSpeed_ * MyMathUtility::Sin(acceleration_);
		speed_ = MyMathUtility::Clamp(speed_, minSpeed_, maxSpeed_);
	}
}

void GameCamera::ThirdPersonUpdate(Mathematics::Vector3& move, Mathematics::Vector3& rot)
{
	//���[���h�g�����X�t�H�[���̐��l�����Z
	thirdPersonTransform_.position.x += move.x;
	thirdPersonTransform_.position.y -= move.y;
	thirdPersonTransform_.position.z += move.z;
	thirdPersonTransform_.rotation += rot;

	//���[���h�g�����X�t�H�[���̍X�V
	thirdPersonTransform_.matWorld = Mathematics::MakeWorldMatrix4(thirdPersonTransform_);
	thirdPersonCamera_->eye_ = Mathematics::GetWorldPosition(thirdPersonTransform_);

	//���[���h�O���x�N�g��
	Mathematics::Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = Mathematics::Vec3Mat4Mul(forward, thirdPersonTransform_.matWorld);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	thirdPersonCamera_->target_ = thirdPersonCamera_->eye_ + forward;
	//���[���h����x�N�g��
	Mathematics::Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	thirdPersonCamera_->up_ = Mathematics::Vec3Mat4Mul(up, thirdPersonTransform_.matWorld);
}

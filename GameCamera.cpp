#include "GameCamera.h"

void GameCamera::Initialize()
{
	input_ = Input::GetInstace();

	GameCamera_ = std::make_unique<Camera>();
	GameCamera_->SetFarZ(40000.0f);
	GameCamera_->Initialize();
	GameCameraTransform_.position = { 0.0f,4000.0f,-5000.0f };
}

void GameCamera::Update()
{
	Mathematics::Vector3 move(0, 0, 0);
	Mathematics::Vector3 front;
	Mathematics::Vector3 frontVec;
	Mathematics::Vector3 frontNormVec;

	float rotationSpeed = 0.01f;

	// �R���g���[���[����
	GameCameraTransform_.rotation.y += rotationSpeed * input_->GetLeftStickVec().x;
	GameCameraTransform_.rotation.x += rotationSpeed * input_->GetLeftStickVec().y;

	// �L�[�{�[�h����
	GameCameraTransform_.rotation.y += rotationSpeed * input_->GetKeyTime(DIK_D) / 254.0f;
	GameCameraTransform_.rotation.y += rotationSpeed * -input_->GetKeyTime(DIK_A) / 254.0f;
	GameCameraTransform_.rotation.x += rotationSpeed * input_->GetKeyTime(DIK_W) / 254.0f;
	GameCameraTransform_.rotation.x += rotationSpeed * -input_->GetKeyTime(DIK_S) / 254.0f;

	front.x = GameCameraTransform_.position.x + cosf(GameCameraTransform_.rotation.y - MyMathUtility::PIHalf);
	front.y = GameCameraTransform_.position.y + cosf(GameCameraTransform_.rotation.x - MyMathUtility::PIHalf);
	front.z = GameCameraTransform_.position.z - sinf(GameCameraTransform_.rotation.y - MyMathUtility::PIHalf);

	frontVec = front - GameCameraTransform_.position;
	frontNormVec = frontVec.normalize();
	front_ = frontNormVec;
	Move();
	moveSpeed_ = speed_ * frontNormVec;
	ThirdPersonUpdate(moveSpeed_, rotSpeed_);
}

Camera* GameCamera::GetCamera()
{
	return GameCamera_.get();
}

float GameCamera::GetSpeed()
{
	return speed_;
}

Object3d* GameCamera::GetTransform()
{
	return &GameCameraTransform_;
}

Mathematics::Vector3 GameCamera::GetWorldPosition()
{
	return Mathematics::GetWorldPosition(GameCameraTransform_);
}

void GameCamera::SetPos(Mathematics::Vector3 pos)
{
	GameCameraTransform_.position = pos;
	GameCameraTransform_.rotation = { 0.0f,0.0f,0.0f };
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
	GameCameraTransform_.position.x += move.x;
	GameCameraTransform_.position.y -= move.y;
	GameCameraTransform_.position.z += move.z;
	GameCameraTransform_.rotation += rot;

	//���[���h�g�����X�t�H�[���̍X�V
	GameCameraTransform_.matWorld = Mathematics::MakeWorldMatrix4(GameCameraTransform_);
	GameCamera_->eye_ = Mathematics::GetWorldPosition(GameCameraTransform_);

	//���[���h�O���x�N�g��
	Mathematics::Vector3 forward(0, 0, 1);
	//���[���J�����̉�]�𔽉f
	forward = Mathematics::Vec3Mat4Mul(forward, GameCameraTransform_.matWorld);
	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	GameCamera_->target_ = GameCamera_->eye_ + forward;
	//���[���h����x�N�g��
	Mathematics::Vector3 up(0, 1, 0);
	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	GameCamera_->up_ = Mathematics::Vec3Mat4Mul(up, GameCameraTransform_.matWorld);
}

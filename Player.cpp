#include "Player.h"
#include <cassert>

Player::~Player()
{
	/*delete playerModel_;
	delete bulletModel_;*/
	delete playerObject_;
	delete bulletObject_;
}

void Player::Initialize(Model* model)
{
	input_ = Input::GetInstace();

	// NULLポインタチェック
	assert(model);
	playerModel_ = model;
	bulletModel_ = Model::LoadFromObj("player");

	playerObject_ = Object3d::Create();
	bulletObject_ = Object3d::Create();
	playerObject_->SetModel(model);
	bulletObject_->SetModel(bulletModel_);

	playerObject_->SetScale({ 1.0f,1.0f,1.0f });
}

void Player::Update(Camera* camera)
{
	// 行列を転送
	playerObject_->Update(camera);

	PlayerMove();
}

void Player::Draw()
{
	playerObject_->Draw();
	if (input_->TriggerPushKey(DIK_SPACE))
	{
		bulletObject_->Draw();
	}
}

void Player::PlayerMove()
{
	playerPos.y = 0.0f;

	if (input_->PushKey(DIK_W))
	{
		playerPos.z += 0.2f;
	}
	if (input_->PushKey(DIK_S))
	{
		playerPos.z -= 0.2f;
	}
	if (input_->PushKey(DIK_A))
	{
		playerPos.x -= 0.2f;
	}
	if (input_->PushKey(DIK_D))
	{
		playerPos.x += 0.2f;
	}

	playerObject_->SetPosition({ playerPos.x, playerPos.y, playerPos.z });
}

void Player::BulletShot()
{
	bulletPos = playerPos;


}

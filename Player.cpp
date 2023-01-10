#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model)
{
	input_ = Input::GetInstace();

	// NULLポインタチェック
	assert(model);
	playerModel_ = model;
	//bulletModel_ = Model::LoadFromObj("bullet");

	playerObject_ = Object3d::Create();
	playerObject_->SetModel(model);

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

}

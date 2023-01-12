#include "Player.h"
#include <cassert>

Player::~Player()
{
	/*delete playerModel_;
	delete bulletModel_;*/
	/*delete playerObject_;
	delete bulletObject_;*/
}

void Player::Initialize(std::unique_ptr<Model>& model)
{
	input_ = Input::GetInstace();

	// NULLポインタチェック
	assert(model);
	bulletModel_.reset(Model::LoadFromObj("skydome"));

	playerObject_.reset(Object3d::Create());
	bulletObject_.reset(Object3d::Create());
	playerObject_->SetModel(model.get());
	bulletObject_->SetModel(bulletModel_.get());

	playerObject_->SetScale({ 1.0f,1.0f,1.0f });
	bulletObject_->SetScale({ 10.0f,10.0f,10.0f });
}

void Player::Update(Camera* camera)
{
	// 行列を転送
	playerObject_->Update(camera);
	bulletObject_->Update(camera);

	PlayerMove();
}

void Player::Draw()
{
	playerObject_->Draw();
	bulletObject_->Draw();
	if (input_->TriggerPushKey(DIK_SPACE))
	{
		
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
	//bulletPos = playerPos;


}

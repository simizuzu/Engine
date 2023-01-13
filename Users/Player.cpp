#include "Player.h"

Player::Player(){}

Player::~Player(){}

void Player::Initialize(Object3d* trans)
{
	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("tire"));
	worldTransform_ = std::make_unique<Object3d>();
	worldTransform_.reset(Object3d::Create());
	worldTransform_->parent = trans;
	worldTransform_->SetPosition({ 0.0f, -2.0f, 10.0f });
	worldTransform_->Initialize();

	collider_.center = Mathematics::GetWorldPosition(*worldTransform_);

	confusionHandle = AudioManager::GetInstance()->LoadAudio("Resources/musics/confusion.mp3");

	//当たり判定の大きさ
	collider_.size = {
		0.3f * worldTransform_->scale.x,
		0.5f * worldTransform_->scale.y,
		0.5f * worldTransform_->scale.z };
}

void Player::Update()
{
	if (!crashFlag)
	{
		if (!rollStopFlag)
		{
			worldTransform_->rotation += {0.2f, 0.0f, 0.0f};
		}

		//移動
		Move();
		//旋回
		Rotate();

		if (Input::GetInstance()->TriggerPushKey(DIK_SPACE) && jumpFlag == 0 && !squatFlag)
		{
			jumpFlag = 1;
		}
	}
	else
	{
		if (jumpFlag == 1)
		{
			jumpFlag = 2;
		}

		worldTransform_->rotation += {0.0f, 0.4f, 0.0f};

		crashTime--;

		if (crashTime == 0)
		{
			crashFlag = false;
			worldTransform_->rotation.y = oldRotY;
			crashTime = 70;
		}
	}

	//ジャンプ
	Jump();
}

void Player::titleUpdate()
{
	if (!rollStopFlag)
	{
		worldTransform_->rotation += {0.2f, 0.0f, 0.0f};
	}
}

void Player::Draw(Camera* camera)
{
	//行列計算
	worldTransform_->Update(camera);

	collider_.center = Mathematics::GetWorldPosition(*worldTransform_);

	worldTransform_->Draw();
}

Object3d& Player::GetWorldTransform()
{
	return *worldTransform_;
}

AABB& Player::GetCollider()
{
	return collider_;
}

void Player::OnCollision()
{
	crashFlag = true;
	crashTime = 70;
	oldRot.y = worldTransform_->rotation.y;
	AudioManager::GetInstance()->PlayWave(confusionHandle);
}

bool Player::GetCrashFlag()
{
	return false;
}

void Player::SetTransform(Mathematics::Vector3 position)
{
	worldTransform_->position = position;
}

void Player::EndGameReset()
{
	worldTransform_->rotation = Mathematics::Vector3(0.0f, 0.0f, 0.0f);

	worldTransform_->position = Mathematics::Vector3(0.0f, 0.0f, 10.0f);

	jumpFlag = 0;
	gravitySpeed = defGravitySpeed;
	worldTransform_->position.y = -2.0f;
}

void Player::JumpReset()
{
	jumpFlag = 0;
	gravitySpeed = defGravitySpeed;
	worldTransform_->position.y = -2.0f;
}

void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		worldTransform_->position += {-0.03f, 0.0f, 0.0f};
	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		worldTransform_->position += {0.03f, 0.0f, 0.0f};
	}

	//移動制限
	{
		const float moveLimitX = 4.5;

		worldTransform_->position.x = max(worldTransform_->position.x, -moveLimitX);
		worldTransform_->position.x = min(worldTransform_->position.x, moveLimitX);
	}
}

void Player::Rotate()
{
	if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		Complement(worldTransform_->rotation.y, -40.0f * MyMathUtility::degree2Radius, 10);//横

	}
	else if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_RIGHT))
	{
		Complement(worldTransform_->rotation.y, 40.0f * MyMathUtility::degree2Radius, 10);//横
	}
	else
	{
		Complement(worldTransform_->rotation.y, 0.0f, 10);//横
	}
}

void Player::Complement(float& x1, float x2, float flame)
{
	float distanceX = x2 - x1;//距離を出す
	float dividedDistanceX = distanceX / flame;//距離をflameで割った値

	x1 += dividedDistanceX;//距離をflameで割った値を足す
}

void Player::Jump()
{
	if (jumpFlag == 1)
	{
		worldTransform_->position.y += gravitySpeed;
		gravitySpeed -= 0.05f;

		if (gravitySpeed <= 0)
		{
			jumpFlag = 2;
		}
	}

	//下がる
	if (jumpFlag == 2)
	{
		worldTransform_->position.y -= gravitySpeed;
		gravitySpeed += 0.04f;

		if (gravitySpeed >= defGravitySpeed)
		{
			jumpFlag = 0;
			gravitySpeed = defGravitySpeed;
			worldTransform_->position.y = -2.0f;
		}
	}
}

void Player::Squat()
{
	if (Input::GetInstance()->TriggerPushKey(DIK_DOWN) && !jumpFlag && !squatFlag ||
		Input::GetInstance()->TriggerPushKey(DIK_S) && !jumpFlag && !squatFlag)
	{
		squatFlag = true;
		rollStopFlag = true;
		oldRot = worldTransform_->rotation;
		worldTransform_->rotation = { 0.0f,0.0f,0.0f };
		worldTransform_->rotation.z = 80.0f * MyMathUtility::degree2Radius;

		collider_.size = {
		0.5f * worldTransform_->scale.x,
		0.3f * worldTransform_->scale.y,
		0.5f * worldTransform_->scale.z };

	}

	if (squatFlag)
	{
		worldTransform_->rotation.y = -90.0f * MyMathUtility::degree2Radius;

		squatTime--;

		if (squatTime == 0)
		{
			squatTime = 60 * 2;
			squatFlag = false;
			rollStopFlag = false;
			worldTransform_->rotation = oldRot;

			//当たり判定の大きさ
			collider_.size = {
				0.3f * worldTransform_->scale.x,
				0.5f * worldTransform_->scale.y,
				0.5f * worldTransform_->scale.z };
		}
	}
}


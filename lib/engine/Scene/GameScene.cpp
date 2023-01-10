#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene()
{
	player_->~Player();
}

void GameScene::Initialize()
{
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	input_ = Input::GetInstace();

	playerModel_ = std::make_unique<Model>();
	playerModel_.reset(Model::LoadFromObj("Player"));

	gameHandle = AudioManager::GetInstance()->LoadAudio("Resources/music/titleBGM.mp3",0.05f);
	//AudioManager::GetInstance()->PlayWave(gameHandle, true);

	player_ = std::make_unique<Player>();
	player_->Initialize(playerModel_.get());
}

void GameScene::Update()
{
	switch (scene)
	{
	case title:
		player_->Update(camera_.get());

		if (input_->PushKey(DIK_RIGHT))
		{
			Mathematics::Vector3 eye = camera_->GetEye();
			eye.x -= 1.0f;
			camera_->SetEye(eye);
		}
		else if (input_->PushKey(DIK_LEFT))
		{
			Mathematics::Vector3 eye = camera_->GetEye();
			eye.x += 1.0f;
			camera_->SetEye(eye);
		}

		if (input_->TriggerPushKey(DIK_SPACE))
		{
			scene = game;
		}
		
		break;

	case game:
		if (input_->TriggerPushKey(DIK_1))
		{
			AudioManager::GetInstance()->StopWave(gameHandle);
		}
	}

	camera_->Update();
}

void GameScene::Draw()
{
#pragma region �w�i�X�v���C�g�`��
	
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	player_->Draw();

#pragma region �O�i�X�v���C�g�`��

#pragma endregion
}

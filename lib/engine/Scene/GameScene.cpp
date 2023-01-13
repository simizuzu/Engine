#include "GameScene.h"

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
	player_->Initialize(playerModel_);

	titleBack = std::make_unique<Sprite>();
	titleBack->Initialize();
}

void GameScene::Update()
{
	switch (sceneNum)
	{
	case 0: // タイトルシーン
		
		titleBack->Update({});

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
#pragma region 背景スプライト描画
	
#pragma endregion

#pragma region 3Dオブジェクト描画
	player_->Draw();

#pragma region 前景スプライト描画

#pragma endregion
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

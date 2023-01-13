#include "GameScene.h"

void GameScene::Initialize()
{
	input_ = Input::GetInstace();
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	TextureManager::GetInstance();

	// スプライト
	titleTex_ = TextureManager::Load("Resources/Texture/title.png");
	titleSprite_ = std::make_unique<Sprite>();
	titleSprite_->Initialize();

	// クラス
	skydome_ = std::make_unique<skydome>();
	skydome_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();
}

void GameScene::Update()
{
	switch (scene)
	{
	case 0: // タイトルシーン
		if (input_->TriggerPushKey(DIK_SPACE))
		{
			scene = 1;
		}
		break;

	case 1: // ゲームシーン
		skydome_->Update(camera_.get());
		stage_->Update(camera_.get());
		break;
	case 2:
		
		break;

	case 3:
		
		break;
	}
	camera_->Update();
}

void GameScene::Draw()
{
	switch (scene)
	{
	case 0: // タイトルシーン
		titleSprite_->DrawSprite(titleTex_, { 640.0f,120.0f });
		break;

	case 1: // ゲームシーン
		skydome_->Draw();
		stage_->Draw();
		break;

	case 2:
		break;

	case 3:
		break;
	}

}

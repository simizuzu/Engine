#include "GameScene.h"

void GameScene::Initialize()
{
	input_ = Input::GetInstace();
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();

	skydome_ = std::make_unique<skydome>();
	skydome_->Initialize();
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
		
		break;

	case 1: // ゲームシーン
		skydome_->Draw();
		break;

	case 2:
		break;

	case 3:
		break;
	}

}

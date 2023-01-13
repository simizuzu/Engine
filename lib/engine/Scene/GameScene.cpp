#include "GameScene.h"

void GameScene::Initialize()
{
	input_ = Input::GetInstace();
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	TextureManager::GetInstance();

	// �X�v���C�g
	titleTex_ = TextureManager::Load("Resources/Texture/title.png");
	titleSprite_ = std::make_unique<Sprite>();
	titleSprite_->Initialize();

	// �N���X
	skydome_ = std::make_unique<skydome>();
	skydome_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();
}

void GameScene::Update()
{
	switch (scene)
	{
	case 0: // �^�C�g���V�[��
		if (input_->TriggerPushKey(DIK_SPACE))
		{
			scene = 1;
		}
		break;

	case 1: // �Q�[���V�[��
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
	case 0: // �^�C�g���V�[��
		titleSprite_->DrawSprite(titleTex_, { 640.0f,120.0f });
		break;

	case 1: // �Q�[���V�[��
		skydome_->Draw();
		stage_->Draw();
		break;

	case 2:
		break;

	case 3:
		break;
	}

}

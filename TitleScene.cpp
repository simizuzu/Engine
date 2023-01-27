#include "TitleScene.h"

void TitleScene::Initialize()
{
	input = Input::GetInstace();

	tex = TextureManager::Load("Resources/Texture/title.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	if (input->TriggerPushKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GAMEPLAY");
	}
}

void TitleScene::Draw()
{
	sprite_->DrawSprite(tex, { 0.0f,0.0f });
}

void TitleScene::Finalize()
{
}

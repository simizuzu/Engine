#include "TitleScene.h"

void TitleScene::Initialize()
{
	tex = TextureManager::Load("Resources/Texture/title.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	sprite_->DrawSprite(tex, { 0.0f,0.0f });
}

void TitleScene::Finalize()
{
}

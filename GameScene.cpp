#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{
	std::make_unique<Sprite>();
	sprite_->Initialize();
	tex = TextureManager::Load("Resources/Texture/enemy.png");
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
	sprite_->DrawSprite(tex, { 100.0f,100.0f }, { 1.0f,1.0f,1.0f,1.0f }, { 1.0f,1.0f }, 0.0f, { 0.0f,0.0f }, false, false);
}

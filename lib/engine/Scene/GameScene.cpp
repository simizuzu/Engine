#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

void GameScene::Initialize()
{
	tex = TextureManager::Load("Resources/Texture/enemy.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ComPtr<ID3D12GraphicsCommandList> commandList = dxCommon_->GetCommandList();

	sprite_->DrawSprite(tex, { 100.0f,100.0f });
}

#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

void GameScene::Initialize()
{
	tex = TextureManager::Load("Resources/Texture/enemy.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	
	// 3Dオブジェクト生成
	object3d_ = Object3d::Create();
	object3d_->Update();
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
#pragma region 背景スプライト描画
	
#pragma endregion

#pragma region 3Dオブジェクト描画
	Object3d::PreDraw();


	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	sprite_->DrawSprite(tex, { 100.0f,100.0f });
#pragma endregion
}

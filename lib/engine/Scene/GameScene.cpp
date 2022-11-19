#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

void GameScene::Initialize()
{
	tex = TextureManager::Load("Resources/Texture/enemy.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	
	// 3D�I�u�W�F�N�g����
	object3d_ = Object3d::Create();
	object3d_->Update();
}

void GameScene::Update()
{
}

void GameScene::Draw()
{
#pragma region �w�i�X�v���C�g�`��
	
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	Object3d::PreDraw();


	Object3d::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	sprite_->DrawSprite(tex, { 100.0f,100.0f });
#pragma endregion
}

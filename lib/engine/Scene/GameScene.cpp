#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene()
{
	delete object3d_;
}

void GameScene::Initialize()
{
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();

	tex = TextureManager::Load("Resources/Texture/enemy.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	
	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("door"));

#pragma region 3D�I�u�W�F�N�g����
	object3d_ = Object3d::Create();

#pragma endregion

#pragma region 3D�I�u�W�F�N�g��3D���f�����Ђ��t��
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	object3d_->SetModel(model_.get());

#pragma endregion
}

void GameScene::Update()
{
	{
		Mathematics::Vector3 eye = camera_->GetEye();
		eye.z += 1.0f;
		camera_->SetEye(eye);
	}
	object3d_->Update(camera_.get());
	camera_->Update();
}

void GameScene::Draw()
{
#pragma region �w�i�X�v���C�g�`��
	
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	object3d_->Draw();

#pragma region �O�i�X�v���C�g�`��
	sprite_->DrawSprite(tex, { 10.0f,10.0f });
#pragma endregion
}

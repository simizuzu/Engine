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
	input_ = Input::GetInstace();

	tex = TextureManager::Load("Resources/Texture/enemy.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	
	model_ = std::make_unique<Model>();
	model_.reset(Model::LoadFromObj("skydome"));

	gameHandle = AudioManager::GetInstance()->LoadAudio("Resources/music/titleBGM.mp3",0.05f);
	//AudioManager::GetInstance()->PlayWave(gameHandle, true);

#pragma region 3Dオブジェクト生成
	object3d_ = Object3d::Create();

#pragma endregion

#pragma region 3Dオブジェクトを3Dモデルをひも付け
	// オブジェクトにモデルをひも付ける
	object3d_->SetModel(model_.get());
	
#pragma endregion
}

void GameScene::Update()
{
	switch (scene)
	{
	case title:
		object3d_->SetRotation({ 0.0f,0.0f,0.0f });
		object3d_->SetPosition({ 0.0f,0.0f,0.0f });
		object3d_->SetScale({ 100.0f,100.0f,100.0f });

		if (input_->PushKey(DIK_RIGHT))
		{
			Mathematics::Vector3 eye = camera_->GetEye();
			eye.z -= 1.0f;
			camera_->SetEye(eye);
		}
		else if (input_->PushKey(DIK_LEFT))
		{
			Mathematics::Vector3 eye = camera_->GetEye();
			eye.z += 1.0f;
			camera_->SetEye(eye);
		}

		if (input_->TriggerPushKey(DIK_SPACE))
		{
			scene = game;
		}
		
		break;

	case game:
		if (input_->TriggerPushKey(DIK_1))
		{
			AudioManager::GetInstance()->StopWave(gameHandle);
		}
	}

	/*{
		Mathematics::Vector3 eye = camera_->GetEye();
		eye.z += 1.0f;
		camera_->SetEye(eye);
	}*/
	object3d_->Update(camera_.get());
	camera_->Update();
}

void GameScene::Draw()
{
#pragma region 背景スプライト描画
	
#pragma endregion

#pragma region 3Dオブジェクト描画
	object3d_->Draw();

#pragma region 前景スプライト描画
	switch (scene)
	{
	case Scene::title:
		sprite_->DrawSprite(tex, { 100.0f,100.0f });
		if (input_->TriggerPushKey(DIK_SPACE))
		{
			scene = Scene::game;
		}
		break;

	case Scene::game:

		sprite_->DrawSprite(tex, { 10.0f,10.0f });
	}
#pragma endregion
}

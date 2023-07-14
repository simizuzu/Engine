#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();
	light_ = std::make_unique<Light>();
	light_.reset(Light::Create());
	Object3d::SetLight(light_.get());

	camera = std::make_unique<Camera>();
	camera->Initialize();

	tyoinori = std::make_unique<ObjModel>();

	//tyoinori.reset(ObjModel::LoadFromObj("tyoinori"));
	tyoinoriObj.reset(Object3d::Create());
	tyoinoriObj->SetModel(tyoinori.get());

	//AudioManager::GetInstance()->PlayWave(gameHandle_);

	sceneManager_ = SceneManager::GetInstance();
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	light_->Update();
	tyoinoriObj->SetScale({10.0f,10.0f,10.0f});
	tyoinoriObj->Update(camera.get());

	camera->Update();
}

void GameScene::Draw()
{
	tyoinoriObj->Draw();
}

void GameScene::Finalize()
{
}

#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize();
	light.reset(Light::Create());
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light.get());

	skydomeModel_ = std::make_unique<ObjModel>();
	skydomeModel_.reset(ObjModel::LoadFromObj("skydome",true));
	skydomeObj_.reset(Object3d::Create());
	skydomeObj_->SetModel(skydomeModel_.get());

	skydomeTrans.Initialize();
	skydomeTrans.SetScale({5.0f,5.0f,5.0f});

	sceneManager_ = SceneManager::GetInstance();
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	camera->Update();
	light->Update();

	skydomeTrans.Update(camera.get());
}

void GameScene::Draw()
{
	skydomeObj_->Draw(&skydomeTrans);
}

void GameScene::Finalize()
{
}

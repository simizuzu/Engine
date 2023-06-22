#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

	tyoinori = std::make_unique<ObjModel>();

	tyoinori.reset(ObjModel::LoadFromObj("tyoinori"));
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
		//AudioManager::GetInstance()->StopWave(gameHandle_);
	}

	// ImGuiウィンドウの表示オン
	ImGui::Begin("Obj");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,40 });
	ImGui::SliderFloat3("obj", &posObj.x, 0.0f, 50.0f, "%.1f");
	ImGui::End();

	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,100 });
	ImGui::SliderFloat3("camera", &cameraPos.y, -10.0f, 40.0f, "%.1f");
	ImGui::End();

	camera->SetTarget({ cameraPos.x ,cameraPos.y ,cameraPos.z});

	tyoinoriObj->SetPosition({ posObj.x, posObj.y ,posObj.z });
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

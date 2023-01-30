#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

	tyoinori = std::make_unique<Model>();

	tyoinori.reset(Model::LoadFromObj("Tyoinori"));
	tyoinoriObj.reset(Object3d::Create());
	tyoinoriObj->SetModel(tyoinori.get());

	sceneManager_ = SceneManager::GetInstance();
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	// ImGuiウィンドウの表示オン
	ImGui::Begin("Obj");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat3("obj", &posObj.x, 0.0f, 50.0f, "%.1f");
	ImGui::End();

	tyoinoriObj->SetPosition({ posObj.x, posObj.y ,posObj.z });
	tyoinoriObj->SetScale({100.0f,100.0f,100.0f});
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

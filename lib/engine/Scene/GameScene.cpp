#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();
}

void GameScene::Update()
{
	// ImGui�E�B���h�E�̕\���I��
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat2("position", pos, 0.0f, 1280.0f, "%1f");
}

void GameScene::Draw()
{
	
}

void GameScene::Finalize()
{
}

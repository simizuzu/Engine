#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

	tex = TextureManager::Load("Resources/Texture/Result.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();

	sceneManager_ = SceneManager::GetInstance();
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE))
	{
		sceneManager_->ChangeScene("TITLE");
	}

	// ImGuiウィンドウの表示オン
	ImGui::Begin("GameScene");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat2("position", &pos.x, 0.0f, 500.0f, "%.1f");
	ImGui::End();

	camera->Update();
}

void GameScene::Draw()
{
	sprite_->DrawSprite(tex, {pos.x,pos.y});
}

void GameScene::Finalize()
{
}

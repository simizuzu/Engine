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
		// ゲームプレイシーン（次シーンを生成）
		BaseScene* scene = new TitleScene();
		// シーン切り替え依頼
		sceneManager_->SetNextScene(scene);
	}
	// ImGuiウィンドウの表示オン
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat2("position", pos, 0.0f, 1280.0f, "%1f");
	camera->Update();
}

void GameScene::Draw()
{
	sprite_->DrawSprite(tex, { 0.0f,0.0f });
}

void GameScene::Finalize()
{
}

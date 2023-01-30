#include "TitleScene.h"
#include "imgui.h"

void TitleScene::Initialize()
{
	input_ = Input::GetInstace();

	tex = TextureManager::Load("Resources/Texture/title.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();
	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	ImGui::Begin("TitleScene");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SliderFloat2("position", &pos.x, 0.0f, 500.0f, "%.1f");
	ImGui::End();

	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("GAMEPLAY");
	}
}

void TitleScene::Draw()
{
	sprite_->DrawSprite(tex, { pos.x,pos.y });
}

void TitleScene::Finalize()
{
}

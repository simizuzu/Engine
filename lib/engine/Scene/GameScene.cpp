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
		// �Q�[���v���C�V�[���i���V�[���𐶐��j
		BaseScene* scene = new TitleScene();
		// �V�[���؂�ւ��˗�
		sceneManager_->SetNextScene(scene);
	}
	// ImGui�E�B���h�E�̕\���I��
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

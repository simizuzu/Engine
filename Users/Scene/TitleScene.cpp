#include "TitleScene.h"
#include "imgui.h"

void TitleScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

	tex = TextureManager::Load("Resources/Texture/title.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();

	tyoinori = std::make_unique<Model>();

	tyoinori.reset(Model::LoadFromObj("tyoinori"));
	tyoinoriObj.reset(Object3d::Create());
	tyoinoriObj->SetModel(tyoinori.get());

	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,100 });
	ImGui::SliderFloat3("camera", &cameraPos.y, -10.0f, 40.0f, "%.1f");
	ImGui::End();

	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("GAMEPLAY");
	}
	camera->SetTarget({ cameraPos.x ,cameraPos.y ,cameraPos.z });

	tyoinoriObj->SetScale({ 10.0f,10.0f,10.0f });
	tyoinoriObj->Update(camera.get());

	camera->Update();
}

void TitleScene::Draw()
{
	sprite_->DrawSprite(tex, { 0,0 });
	tyoinoriObj->Draw();
}

void TitleScene::Finalize()
{
}

#include "TitleScene.h"
#include "imgui.h"

void TitleScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

#pragma region Sprite
	tex = TextureManager::Load("Resources/Texture/title.png");
	sprite_ = std::make_unique<Sprite>();
	sprite_->Initialize();

	tex2 = TextureManager::Load("Resources/Texture/warning.png");
	warningSprite_ = std::make_unique<Sprite>();
	warningSprite_->Initialize();
#pragma endregion

#pragma region OBJ
	tyoinori = std::make_unique<Model>();
	tyoinori.reset(Model::LoadFromObj("tyoinori"));
	tyoinoriObj.reset(Object3d::Create());
	tyoinoriObj->SetModel(tyoinori.get());

	skydome = std::make_unique<Model>();
	skydome.reset(Model::LoadFromObj("skydome"));
	skydomeObj.reset(Object3d::Create());
	skydomeObj->SetModel(skydome.get());
#pragma endregion

#pragma region Particle
	particles_ = std::make_unique<ParticleManager>();
	particles_->Initialize();
	particles_->LoadTexture(L"Resources/effect.png");
	particleTrans_.Initialize();

	particles2_ = std::make_unique<ParticleManager>();
	particles2_->Initialize();
	particles2_->LoadTexture(L"Resources/Texture/warning.png");
	particleTrans2_.Initialize();
#pragma endregion

	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,100 });
	ImGui::SliderFloat2("camera", &cameraPos.y, -10.0f, 100.0f, "%.1f");
	ImGui::SliderFloat3("camera", &cameraPos.x, -10.0f, 100.0f, "%.1f");
	ImGui::End();

	camera->SetTarget({ cameraPos.x ,cameraPos.y ,cameraPos.z });

	tyoinoriObj->SetScale({ 10.0f,10.0f,10.0f });
	tyoinoriObj->SetPosition({ 0.0f,-20.0f,0.0f });
	tyoinoriObj->Update(camera.get());

	skydomeObj->SetScale({ 0.05f,0.05f,0.05f });
	skydomeObj->SetPosition({ 0.0f,0.0f,-20.0f });
	skydomeObj->Update(camera.get());

	particles_->RandParticle();
	particles_->Update();
	particleTrans_.SetTranslation({ 20.0f,0.0f,0.0f });
	particleTrans_.Update(camera.get());

	particles2_->RandParticle();
	particles2_->Update();
	particleTrans2_.SetTranslation({ -20.0f,0.0f,0.0f });
	particleTrans2_.Update(camera.get());

	camera->Update();
}

void TitleScene::Draw()
{
	sprite_->DrawSprite(tex, { 500.0f,200.0f },{0.5f,0.5f});
	warningSprite_->DrawSprite(tex2, { 20.0f,20.0f });
	skydomeObj->Draw();
	tyoinoriObj->Draw();
	particles_->Draw(&particleTrans_);
	particles2_->Draw(&particleTrans2_);
}

void TitleScene::Finalize()
{
}

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
	tyoinori.reset(Model::LoadFromObj("Enemy"));
	tyoinoriObj.reset(Object3d::Create());
	tyoinoriObj->SetModel(tyoinori.get());
	tyoinoriObj->SetScale({ 10.0f,10.0f,10.0f });

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

	//camera->SetEye({ 0.0f, 0.0f, 0.0f });

	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	camera->Update();
	/*ImGui::Begin("camera");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,100 });
	ImGui::SliderFloat2("camera", &cameraPos.y, -10.0f, 100.0f, "%.1f");
	ImGui::SliderFloat3("camera", &cameraPos.x, -10.0f, 100.0f, "%.1f");
	ImGui::End();*/
	//tyoinoriObj->SetPosition({ 0.0f,-20.0f,0.0f });

	if (input_->PushKey(DIK_RIGHT))
	{
		rot++;
	}
	else if (input_->PushKey(DIK_LEFT))
	{
		rot--;
	}
	tyoinoriObj->SetRotation({ 0.0f,rot,0.0f });
	tyoinoriObj->Update(camera.get());

}

void TitleScene::Draw()
{
	//sprite_->DrawSprite(tex, { 500.0f,200.0f },{0.5f,0.5f});
	//warningSprite_->DrawSprite(tex2, { 20.0f,20.0f });
	//skydomeObj->Draw();
	tyoinoriObj->Draw();
	//particles_->Draw(&particleTrans_);
	//particles2_->Draw(&particleTrans2_);
}

void TitleScene::Finalize()
{
}

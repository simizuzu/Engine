#include "TitleScene.h"
#include "imgui.h"

void TitleScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();

	light.reset(Light::Create());
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light.get());

	sceneManager_ = SceneManager::GetInstance();
}

void TitleScene::Update()
{
	camera->Update();
	light->Update();
}

void TitleScene::Draw()
{

}

void TitleScene::Finalize()
{
}

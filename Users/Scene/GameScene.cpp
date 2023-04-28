#include "GameScene.h"

#include <imgui.h>

void GameScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();
	sceneManager_ = SceneManager::GetInstance();

	cube = Model::LoadFromObj("cube");

	levelData = LevelLoader::LoadFile("Test");
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("TITLE");
		//AudioManager::GetInstance()->StopWave(gameHandle_);
	}

	ImGui::Begin("camera");
	ImGui::SetWindowSize({ 500,100 });
	ImGui::SetWindowPos({ 100,100 });
	ImGui::SliderFloat3("camera", &cameraPos.y, -10.0f, 40.0f, "%.1f");
	ImGui::End();

	// レベルデータからオブジェクトを生成、配置
	for (auto& objectData : levelData->objects) {
		// ファイル名から登録済みモデルを検索
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) {
			model = it->second;
		}

		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create();

		// 座標
		Mathematics::Vector3 pos;
		newObject->SetPosition(pos);

		// 回転角
		Mathematics::Vector3 rot;
		newObject->SetRotation(rot);

		// 座標
		Mathematics::Vector3 scale;
		newObject->SetScale(scale);

		// 配列に登録
		objects.push_back(newObject);
	}

	camera->SetTarget({ cameraPos.x ,cameraPos.y ,cameraPos.z});

	camera->Update();
}

void GameScene::Draw()
{

}

void GameScene::Finalize()
{
}

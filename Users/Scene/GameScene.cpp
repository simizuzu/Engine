#include "GameScene.h"

#include <imgui.h>

GameScene::~GameScene()
{
	for (Object3d*& object : objects) {
		delete object;
	}
	delete levelData;
	delete Tire;
	delete Sphere;
	delete Map01;
}

void GameScene::Initialize()
{
	input_ = Input::GetInstace();

	camera = std::make_unique<Camera>();
	camera->Initialize();
	sceneManager_ = SceneManager::GetInstance();

	levelData = LevelLoader::LoadFile("Test");

	Tire = Model::LoadFromObj("Tire");
	models.insert(std::make_pair("Tire", Tire));

	Sphere = Model::LoadFromObj("Sphere");
	models.insert(std::make_pair("Sphere", Sphere));

	Map01 = Model::LoadFromObj("Map01");
	models.insert(std::make_pair("Map01", Map01));

	//models.insert(std::make_pair("Cylinder", cylinder));

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
		newObject->SetModel(model);

		// 座標
		Mathematics::Vector3 pos;
		pos = objectData.translation;
		newObject->SetPosition(pos);

		// 回転角
		Mathematics::Vector3 rot;
		rot = objectData.rotation;
		newObject->SetRotation(rot);

		// 座標
		Mathematics::Vector3 scale;
		scale = objectData.scaling;
		newObject->SetScale(scale);

		// 配列に登録
		objects.push_back(newObject);
	}
}

void GameScene::Update()
{
	if (input_->TriggerPushKey(DIK_SPACE) || input_->TriggerButton(A))
	{
		sceneManager_->ChangeScene("TITLE");
		//AudioManager::GetInstance()->StopWave(gameHandle_);
	}

	camera->SetTarget({ 0,0,0 });
	camera->SetEye({ 0.0f,0.0f,-10.0f });

	for (auto& object : objects) {
		object->Update(camera.get());
	}

	camera->Update();
}

void GameScene::Draw()
{
	for (auto& object : objects) {
		object->Draw();
	}
}

void GameScene::Finalize()
{
}

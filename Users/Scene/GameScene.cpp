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

	// ���x���f�[�^����I�u�W�F�N�g�𐶐��A�z�u
	for (auto& objectData : levelData->objects) {
		// �t�@�C��������o�^�ς݃��f��������
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) {
			model = it->second;
		}

		// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);

		// ���W
		Mathematics::Vector3 pos;
		pos = objectData.translation;
		newObject->SetPosition(pos);

		// ��]�p
		Mathematics::Vector3 rot;
		rot = objectData.rotation;
		newObject->SetRotation(rot);

		// ���W
		Mathematics::Vector3 scale;
		scale = objectData.scaling;
		newObject->SetScale(scale);

		// �z��ɓo�^
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

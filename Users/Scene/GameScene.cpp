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

		// ���W
		Mathematics::Vector3 pos;
		newObject->SetPosition(pos);

		// ��]�p
		Mathematics::Vector3 rot;
		newObject->SetRotation(rot);

		// ���W
		Mathematics::Vector3 scale;
		newObject->SetScale(scale);

		// �z��ɓo�^
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

#include "SceneManager.h"

void SceneManager::Update()
{
	// ���̃V�[���̗\�񂪂���Ȃ�
	if (nextScene_)
	{
		// ���V�[���̏I��
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}

		// �V�[���؂�ւ�
		scene_ = nextScene_;
		nextScene_ = nullptr;

		// �V�[���}�l�[�W�����Z�b�g
		scene_->SetSceneManager(this);

		// ���̃V�[��������������
		scene_->Initialize();
	}

	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}

void SceneManager::Finalize()
{
	// �Ō�̃V�[���̏I���Ɖ��
	scene_->Finalize();
	delete scene_;
}

void SceneManager::SetNextScene(BaseScene* nextScene)
{
	nextScene_ = nextScene;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager sceneManager;

	return &sceneManager;
}

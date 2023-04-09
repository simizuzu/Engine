#include "MainGame.h"

void MainGame::Initialize()
{
	// ���N���X�̏���������
	Framework::Initialize();
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);
	//�p�[�e�B�N���}�l�[�W���[�ÓI������
	ParticleManager::StaticInitialize(dxCommon_->GetDevice(), dxCommon_->GetCommandList());

	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);
	SceneManager::GetInstance()->ChangeScene("TITLE");
}

void MainGame::Finalize()
{
	// ���N���X�̏I������
	Framework::Finalize();
}

void MainGame::Update()
{
	// ���N���X�̍X�V����
	Framework::Update();
}

void MainGame::Draw()
{
	// �Q�[���V�[���̕`��
	//baseScene->Draw();
	sceneManager_->Draw();
}

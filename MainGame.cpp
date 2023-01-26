#include "MainGame.h"

void MainGame::Initialize()
{
	// ���N���X�̏���������
	Framework::Initialize();


	textureManager_ = TextureManager::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();


	// �X�v���C�g���ʕ��̏�����
	textureManager_->Initialize(dxCommon_);
	// ImGui������
	imGuiManager->Initialize(winApp_, dxCommon_);
	
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);

	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MainGame::Finalize()
{
	// �e�N�X�`���}�l�[�W�����
	textureManager_->Delete();
	// ImGui���
	imGuiManager->Finalize();

	// ���N���X�̏I������
	Framework::Finalize();
}

void MainGame::Update()
{
	// ���N���X�̍X�V����
	Framework::Update();

	// ImGui�X�V�����J�n
	imGuiManager->Begin();
	// �Q�[���V�[���̖��t���[������
	gameScene->Update();
	// ImGui�X�V�����I��
	imGuiManager->End();
}

void MainGame::Draw()
{
	// �Q�[���V�[���̕`��
	gameScene->Draw();
	//ImGui�`��
	imGuiManager->Draw(dxCommon_);
}

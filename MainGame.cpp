#include "MainGame.h"

void MainGame::Initialize()
{
	// ���N���X�̏���������
	Framework::Initialize();
	winApp_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstace();
	textureManager_ = TextureManager::GetInstance();
	audioManager = AudioManager::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();

	// WindowsAPI������
	winApp_->Initialize();
	// DirectX������
	dxCommon_->Initialize();
	// FPS�Œ菉����
	fps_ = new FPS();
	fps_->InitializeFixFps();
	// Audio������
	audioManager->Initialize();
	// Input������
	input_->Initialize();
	// ImGui������
	imGuiManager->Initialize(winApp_, dxCommon_);

	// �X�v���C�g���ʕ��̏�����
	textureManager_->Initialize(dxCommon_);

	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize();
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);

	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MainGame::Finalize()
{

	// �e�N�X�`���}�l�[�W�����
	textureManager_->Delete();
	audioManager->Destroy();
	// ImGui���
	imGuiManager->Finalize();
	// DirectX���
	dxCommon_->Delete();
	// WindowsAPI�̏I������
	winApp_->Finalize();
	// WinApp���
	winApp_->Delete();
	// FPS���
	delete fps_;

	// ���N���X�̏I������
	Framework::Finalize();
}

void MainGame::Update()
{
	// ���N���X�̍X�V����
	Framework::Update();

	// Windows�̃��b�Z�[�W����
	if (winApp_->ProccessMessage())
	{
		endRequest_ = true;
	}

	// ImGui�X�V�����J�n
	imGuiManager->Begin();
	// ���͂̍X�V
	input_->Update();
	audioManager->Update();
	// �Q�[���V�[���̖��t���[������
	gameScene->Update();
	// ImGui�X�V�����I��
	imGuiManager->End();
}

void MainGame::Draw()
{
	// �`��O����
	dxCommon_->PreDraw(winApp_);
	// �Q�[���V�[���̕`��
	gameScene->Draw();
	//ImGui�`��
	imGuiManager->Draw(dxCommon_);
	// �`��㏈��
	dxCommon_->PostDraw();
	// FPS�Œ�X�V
	fps_->UpdateFixFPS();
}

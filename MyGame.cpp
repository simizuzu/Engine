#include "MyGame.h"

void MyGame::Initialize()
{
	// WindowsAPI������
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize();

	// DirectX������
	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize();

	// FPS�Œ菉����
	fps_ = new FPS();
	fps_->InitializeFixFps();

	// Input������
	input_ = new Input();
	input_->Initialize();

	// �X�v���C�g���ʕ��̏�����
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	// �X�v���C�g�̏�����
	Sprite::StaticInitialize();

	std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MyGame::Finalize()
{
	textureManager_->Delete();
	// ���͉��
	delete input_;
	// DirectX���
	dxCommon_->Delete();
	// WindowsAPI�̏I������
	winApp_->Finalize();
	// WinApp���
	winApp_->Delete();
	// FPS���
	delete fps_;
}

void MyGame::Update()
{
	// �Q�[�����[�v
	while (true) {
		// Windows�̃��b�Z�[�W����
		if (winApp_->ProccessMessage())
		{
			// �Q�[�����[�v�𔲂���
			break;
		}
		// ���͂̍X�V
		input_->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();
	}
}

void MyGame::Draw()
{
	// �`��O����
	dxCommon_->PreDraw(winApp_);
	// �Q�[���V�[���̕`��
	gameScene->Draw();
	// �`��㏈��
	dxCommon_->PostDraw();
	// FPS�Œ�X�V
	fps_->UpdateFixFPS();
}

#include "Framework.h"

void Framework::Initialize()
{
	winApp_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstace();
	audioManager = AudioManager::GetInstance();

	// WindowsAPI������
	winApp_->Initialize();
	// DirectX������
	dxCommon_->Initialize();
	// Audio������
	audioManager->Initialize();
	// Input������
	input_->Initialize();
	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize();
	// FPS�Œ菉����
	fps_ = new FPS();
	fps_->InitializeFixFps();
}

void Framework::Finalize()
{
	audioManager->Destroy();
	// DirectX���
	dxCommon_->Delete();
	// WindowsAPI�̏I������
	winApp_->Finalize();
	// WinApp���
	winApp_->Delete();
	// FPS���
	delete fps_;
}

void Framework::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp_->ProccessMessage())
	{
		endRequest_ = true;
	}
	// ���͂̍X�V
	input_->Update();
	audioManager->Update();
}

void Framework::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v
	{
		// ���t���[���X�V
		Update();
		// �I�����N�G�X�g�������甲����
		if (IsEndRequest())
		{
			break;
		}
		dxCommon_->PreDraw(winApp_);
		// �`��
		Draw();
		dxCommon_->PostDraw();
		// FPS�Œ�X�V
		fps_->UpdateFixFPS();
	}
	// �Q�[���I��
	Finalize();
}

bool Framework::IsEndRequest()
{
	return endRequest_;
}

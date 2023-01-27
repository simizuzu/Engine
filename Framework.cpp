#include "Framework.h"

void Framework::Initialize()
{
	winApp_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstace();
	audioManager = AudioManager::GetInstance();
	textureManager_ = TextureManager::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();

	// WindowsAPI������
	winApp_->Initialize();
	// FPS�Œ菉����
	fps_ = new FPS();
	fps_->InitializeFixFps();
	// DirectX������
	dxCommon_->Initialize();
	// �X�v���C�g���ʕ��̏�����
	textureManager_->Initialize(dxCommon_);
	// Audio������
	audioManager->Initialize();
	// ImGui������
	imGuiManager->Initialize(winApp_, dxCommon_);
	// Input������
	input_->Initialize();
	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize();

	/*gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();*/

	sceneManager_ = SceneManager::GetInstance();
}

void Framework::Finalize()
{
	//gameScene->Finalize();
	sceneManager_->Finalize();
	delete sceneFactory_;

	// ImGui���
	imGuiManager->Finalize();
	// �e�N�X�`���}�l�[�W�����
	textureManager_->Delete();
	// �I�[�f�B�I�}�l�[�W���[������
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

	// ImGui�X�V�����J�n
	imGuiManager->Begin();
	// �Q�[���V�[���̖��t���[������
	//gameScene->Update();
	sceneManager_->Update();
	
	// ImGui�X�V�����I��
	imGuiManager->End();
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
		//ImGui�`��
		imGuiManager->Draw(dxCommon_);
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

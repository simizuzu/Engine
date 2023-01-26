#include <Windows.h>
#include <memory>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "Object3d.h"
#include "AudioManager.h"
#include "ImGuiManager.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region ��ՃV�X�e���̏�����

	WinApp* winApp_ = WinApp::GetInstance();
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	FPS* fps_ = nullptr;
	Input* input_ = Input::GetInstace();
	TextureManager* textureManager_ = TextureManager::GetInstance();
	AudioManager* audioManager = AudioManager::GetInstance();
	ImGuiManager* imGuiManager = ImGuiManager::GetInstance();
	Sprite* sprite_ = nullptr;

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
	imGuiManager->Initialize(winApp_,dxCommon_);

	// �X�v���C�g���ʕ��̏�����
	textureManager_->Initialize(dxCommon_);
	// �X�v���C�g�ÓI������
	Sprite::StaticInitialize();
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);
#pragma endregion

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

#pragma region �Q�[�����[�v
	// �Q�[�����[�v
	while (true) {
		// Windows�̃��b�Z�[�W����
		if (winApp_->ProccessMessage())
		{
			// �Q�[�����[�v�𔲂���
			break;
		}
#pragma region �X�V
		// ImGui�X�V�����J�n
		imGuiManager->Begin();
		// ���͂̍X�V
		input_->Update();
		audioManager->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();
		// ImGui�X�V�����I��
		imGuiManager->End();
#pragma endregion

#pragma region �`��
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
#pragma endregion
	}

#pragma endregion

#pragma region ��ՃV�X�e���̏I��
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
#pragma endregion

	return 0;
}
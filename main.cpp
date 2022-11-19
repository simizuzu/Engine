#include <Windows.h>
#include <memory>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "Shader.h"
#include "Pipeline.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region ��ՃV�X�e���̏�����

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	FPS* fps_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Sprite* sprite_ = nullptr;

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

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

#pragma endregion

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
		// ���͂̍X�V
		input_->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();
#pragma endregion

#pragma region �`��
		// �`��O����
		dxCommon_->PreDraw(winApp_);
		// �Q�[���V�[���̕`��
		gameScene->Draw();
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
	// �V�F�[�_�ƃp�C�v���C���̉��
	sprite_->Delete();
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
#pragma endregion

	return 0;
}
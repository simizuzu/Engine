#include <Windows.h>
#include <memory>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameScene.h"

#include "MyGame.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region ��ՃV�X�e���̏�����
	// WindowsAPI������
	WinApp* winApp_ = nullptr;
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize();

	// DirectX������
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize();

	// FPS�Œ菉����
	FPS* fps_ = nullptr;
	fps_ = new FPS();
	fps_->InitializeFixFps();

	// Input������
	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

	// �X�v���C�g���ʕ��̏�����
	TextureManager* textureManager_ = nullptr;
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	// �X�v���C�g�̏�����
	Sprite::StaticInitialize();

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

	MyGame game;
	game.Initialize();

#pragma endregion

#pragma region �ŏ��̃V�[���̏�����
	

#pragma endregion

#pragma region �Q�[�����[�v
	// �Q�[�����[�v
	while (true){
		// Windows�̃��b�Z�[�W����
		if (winApp_->ProccessMessage())
		{
			// �Q�[�����[�v�𔲂���
			break;
		}

		// ���͂̍X�V
		input_->Update();

		// �`��O����
		dxCommon_->PreDraw(winApp_);

#pragma region �ŏ��̃V�[���̕`��

#pragma endregion

		gameScene->Update();
		gameScene->Draw();
		// �`��㏈��
		dxCommon_->PostDraw();
		// FPS�Œ�X�V
		fps_->UpdateFixFPS();

		game.Draw();
		game.Update();
	}
#pragma endregion

#pragma region ��ՃV�X�e���̏I��
	// �X�v���C�g���
	
	// �e�N�X�`�����
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

	game.Finalize();
#pragma endregion

	return 0;
}
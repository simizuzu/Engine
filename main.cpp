#include <Windows.h>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "SpriteCommon.h"
#include "Sprite.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region ��ՃV�X�e���̏�����
	// WindowsAPI������
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp;
	winApp_->GetInstance()->Initialize();

	// DirectX������
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = new DirectXCommon;
	dxCommon_->Initialize();

	// FPS�Œ菉����
	FPS* fps_ = nullptr;
	fps_ = new FPS;
	fps_->InitializeFixFps();

	// Input������
	Input* input_ = nullptr;
	input_ = new Input;
	input_->Initialize();

	// �X�v���C�g���ʕ��̏�����
	SpriteCommon* spriteCommon_ = nullptr;
	spriteCommon_ = new SpriteCommon;
	spriteCommon_->Initialize(dxCommon_);
#pragma endregion

#pragma region �ŏ��̃V�[���̏�����
	// �X�v���C�g�̏�����
	Sprite* sprite_ = new Sprite();
	sprite_->Initialize(spriteCommon_);
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
		dxCommon_->PreDraw();

		// FPS�Œ�X�V
		fps_->UpdateFixFPS();

#pragma region �ŏ��̃V�[���̕`��

#pragma endregion

		// �`��㏈��
		dxCommon_->PostDraw();
	}
#pragma endregion

#pragma region ��ՃV�X�e���̏I��
	// ���͉��
	delete input_;
	// �X�v���C�g���
	delete sprite_;
	delete spriteCommon_;
	// DirectX���
	delete dxCommon_;
	// WindowsAPI�̏I������
	winApp_->Finalize();
	// �������
	delete winApp_;
#pragma endregion

	return 0;
}
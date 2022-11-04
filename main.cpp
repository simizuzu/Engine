#include <Windows.h>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
	// WindowsAPI������
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp();
	winApp_->GetInstance()->Initialize();

	// DirectX������
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = new DirectXCommon();
	dxCommon_->Initialize();

	// Input������
	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

	// FPS�Œ菉����
	FPS* fps_ = nullptr;
	fps_ = new FPS();
	fps_->InitializeFixFps();

#pragma region �Q�[�����[�v
	// �Q�[�����[�v
	while (true){
		// Windows�̃��b�Z�[�W����
		if (winApp_->ProccessMessage())
		{
			// �Q�[�����[�v�𔲂���
			break;
		}

		dxCommon_->PreDraw();
		fps_->UpdateFixFPS();


		dxCommon_->PostDraw();
	}
#pragma endregion

	// WindowsAPI�̏I������
	winApp_->Finalize();

	// �������
	delete winApp_;
	delete input_;
	delete dxCommon_;

	return 0;
}
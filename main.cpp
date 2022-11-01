#include <Windows.h>

#include "Input.h"
#include "WinApp.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
	// WindowsAPI�̏�����
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp();
	winApp_->GetInstance()->Initialize();

	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

	// WindowsAPI�̏I������
	winApp_->Finalize();

#pragma region �Q�[�����[�v
	// �Q�[�����[�v
	while (true){
		// Windows�̃��b�Z�[�W����
		if (winApp_->ProccessMessage())
		{
			// �Q�[�����[�v�𔲂���
			break;
		}
	}
#pragma endregion

	// WindowsAPI���
	delete winApp_;

	return 0;
}
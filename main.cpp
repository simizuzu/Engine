#include <Windows.h>

#include "Input.h"
#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
	// WindowsAPIの初期化
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp();
	winApp_->GetInstance()->Initialize();

	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

	// WindowsAPIの終了処理
	winApp_->Finalize();

#pragma region ゲームループ
	// ゲームループ
	while (true){
		// Windowsのメッセージ処理
		if (winApp_->ProccessMessage())
		{
			// ゲームループを抜ける
			break;
		}
	}
#pragma endregion

	// WindowsAPI解放
	delete winApp_;

	return 0;
}
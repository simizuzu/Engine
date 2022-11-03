#include <Windows.h>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
	// WindowsAPI初期化
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp();
	winApp_->GetInstance()->Initialize();

	// DirectX初期化
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = new DirectXCommon();
	dxCommon_->Initialize(winApp_);

	// Input初期化
	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

#pragma region ゲームループ
	// ゲームループ
	while (true){
		// Windowsのメッセージ処理
		if (winApp_->ProccessMessage())
		{
			// ゲームループを抜ける
			break;
		}

		dxCommon_->PreDraw();



		dxCommon_->PostDraw();
	}
#pragma endregion

	// WindowsAPIの終了処理
	winApp_->Finalize();

	// 解放処理
	delete winApp_;
	delete input_;
	delete dxCommon_;

	return 0;
}
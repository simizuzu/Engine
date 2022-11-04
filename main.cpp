#include <Windows.h>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "SpriteCommon.h"
#include "Sprite.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region 基盤システムの初期化
	// WindowsAPI初期化
	WinApp* winApp_ = nullptr;
	winApp_ = new WinApp;
	winApp_->GetInstance()->Initialize();

	// DirectX初期化
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = new DirectXCommon;
	dxCommon_->Initialize();

	// FPS固定初期化
	FPS* fps_ = nullptr;
	fps_ = new FPS;
	fps_->InitializeFixFps();

	// Input初期化
	Input* input_ = nullptr;
	input_ = new Input;
	input_->Initialize();

	// スプライト共通部の初期化
	SpriteCommon* spriteCommon_ = nullptr;
	spriteCommon_ = new SpriteCommon;
	spriteCommon_->Initialize(dxCommon_);
#pragma endregion

#pragma region 最初のシーンの初期化
	// スプライトの初期化
	Sprite* sprite_ = new Sprite();
	sprite_->Initialize(spriteCommon_);
#pragma endregion

#pragma region ゲームループ
	// ゲームループ
	while (true){
		// Windowsのメッセージ処理
		if (winApp_->ProccessMessage())
		{
			// ゲームループを抜ける
			break;
		}

		// 入力の更新
		input_->Update();

		// 描画前処理
		dxCommon_->PreDraw();

		// FPS固定更新
		fps_->UpdateFixFPS();

#pragma region 最初のシーンの描画

#pragma endregion

		// 描画後処理
		dxCommon_->PostDraw();
	}
#pragma endregion

#pragma region 基盤システムの終了
	// 入力解放
	delete input_;
	// スプライト解放
	delete sprite_;
	delete spriteCommon_;
	// DirectX解放
	delete dxCommon_;
	// WindowsAPIの終了処理
	winApp_->Finalize();
	// 解放処理
	delete winApp_;
#pragma endregion

	return 0;
}
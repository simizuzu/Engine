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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region 基盤システムの初期化
	// WindowsAPI初期化
	WinApp* winApp_ = nullptr;
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize();

	// DirectX初期化
	DirectXCommon* dxCommon_ = nullptr;
	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize();

	// FPS固定初期化
	FPS* fps_ = nullptr;
	fps_ = new FPS();
	fps_->InitializeFixFps();

	// Input初期化
	Input* input_ = nullptr;
	input_ = new Input();
	input_->Initialize();

	// スプライト共通部の初期化
	TextureManager* textureManager_ = nullptr;
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	// スプライトの初期化
	Sprite::StaticInitialize();

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

	MyGame game;
	game.Initialize();

#pragma endregion

#pragma region 最初のシーンの初期化
	

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
		dxCommon_->PreDraw(winApp_);

#pragma region 最初のシーンの描画

#pragma endregion

		gameScene->Update();
		gameScene->Draw();
		// 描画後処理
		dxCommon_->PostDraw();
		// FPS固定更新
		fps_->UpdateFixFPS();

		game.Draw();
		game.Update();
	}
#pragma endregion

#pragma region 基盤システムの終了
	// スプライト解放
	
	// テクスチャ解放
	textureManager_->Delete();
	// 入力解放
	delete input_;
	// DirectX解放
	dxCommon_->Delete();
	// WindowsAPIの終了処理
	winApp_->Finalize();
	// WinApp解放
	winApp_->Delete();
	// FPS解放
	delete fps_;

	game.Finalize();
#pragma endregion

	return 0;
}
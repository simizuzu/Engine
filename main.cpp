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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region 基盤システムの初期化

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	FPS* fps_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	Sprite* sprite_ = nullptr;

	// WindowsAPI初期化
	winApp_ = WinApp::GetInstance();
	winApp_->Initialize();

	// DirectX初期化
	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize();

	// FPS固定初期化
	fps_ = new FPS();
	fps_->InitializeFixFps();

	// Input初期化
	input_ = new Input();
	input_->Initialize();

	// スプライト共通部の初期化
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize(dxCommon_);

	// スプライトの初期化
	Sprite::StaticInitialize();

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

#pragma endregion

#pragma region ゲームループ
	// ゲームループ
	while (true) {
		// Windowsのメッセージ処理
		if (winApp_->ProccessMessage())
		{
			// ゲームループを抜ける
			break;
		}
#pragma region 更新
		// 入力の更新
		input_->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
#pragma endregion

#pragma region 描画
		// 描画前処理
		dxCommon_->PreDraw(winApp_);
		// ゲームシーンの描画
		gameScene->Draw();
		// 描画後処理
		dxCommon_->PostDraw();
		// FPS固定更新
		fps_->UpdateFixFPS();
#pragma endregion
	}
#pragma endregion

#pragma region 基盤システムの終了
	// テクスチャマネージャ解放
	textureManager_->Delete();
	// シェーダとパイプラインの解放
	sprite_->Delete();
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
#pragma endregion

	return 0;
}
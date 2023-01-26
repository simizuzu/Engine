#include <Windows.h>
#include <memory>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "Object3d.h"
#include "AudioManager.h"
#include "ImGuiManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region 基盤システムの初期化

	WinApp* winApp_ = WinApp::GetInstance();
	DirectXCommon* dxCommon_ = DirectXCommon::GetInstance();
	FPS* fps_ = nullptr;
	Input* input_ = Input::GetInstace();
	TextureManager* textureManager_ = TextureManager::GetInstance();
	AudioManager* audioManager = AudioManager::GetInstance();
	ImGuiManager* imGuiManager = ImGuiManager::GetInstance();
	Sprite* sprite_ = nullptr;

	// WindowsAPI初期化
	winApp_->Initialize();
	// DirectX初期化
	dxCommon_->Initialize();
	// FPS固定初期化
	fps_ = new FPS();
	fps_->InitializeFixFps();
	// Audio初期化
	audioManager->Initialize();
	// Input初期化
	input_->Initialize();
	// ImGui初期化
	imGuiManager->Initialize(winApp_,dxCommon_);

	// スプライト共通部の初期化
	textureManager_->Initialize(dxCommon_);
	// スプライト静的初期化
	Sprite::StaticInitialize();
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);
#pragma endregion

	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();

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
		// ImGui更新処理開始
		imGuiManager->Begin();
		// 入力の更新
		input_->Update();
		audioManager->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		// ImGui更新処理終了
		imGuiManager->End();
#pragma endregion

#pragma region 描画
		// 描画前処理
		dxCommon_->PreDraw(winApp_);
		// ゲームシーンの描画
		gameScene->Draw();
		//ImGui描画
		imGuiManager->Draw(dxCommon_);
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
	audioManager->Destroy();
	// ImGui解放
	imGuiManager->Finalize();
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
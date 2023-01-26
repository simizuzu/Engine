#include "MainGame.h"

void MainGame::Initialize()
{
	// 基底クラスの初期化処理
	Framework::Initialize();
	winApp_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstace();
	textureManager_ = TextureManager::GetInstance();
	audioManager = AudioManager::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();

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
	imGuiManager->Initialize(winApp_, dxCommon_);

	// スプライト共通部の初期化
	textureManager_->Initialize(dxCommon_);

	// スプライト静的初期化
	Sprite::StaticInitialize();
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);

	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MainGame::Finalize()
{

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

	// 基底クラスの終了処理
	Framework::Finalize();
}

void MainGame::Update()
{
	// 基底クラスの更新処理
	Framework::Update();

	// Windowsのメッセージ処理
	if (winApp_->ProccessMessage())
	{
		endRequest_ = true;
	}

	// ImGui更新処理開始
	imGuiManager->Begin();
	// 入力の更新
	input_->Update();
	audioManager->Update();
	// ゲームシーンの毎フレーム処理
	gameScene->Update();
	// ImGui更新処理終了
	imGuiManager->End();
}

void MainGame::Draw()
{
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
}

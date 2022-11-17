#include "MyGame.h"

void MyGame::Initialize()
{
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

	std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MyGame::Finalize()
{
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
}

void MyGame::Update()
{
	// ゲームループ
	while (true) {
		// Windowsのメッセージ処理
		if (winApp_->ProccessMessage())
		{
			// ゲームループを抜ける
			break;
		}
		// 入力の更新
		input_->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
	}
}

void MyGame::Draw()
{
	// 描画前処理
	dxCommon_->PreDraw(winApp_);
	// ゲームシーンの描画
	gameScene->Draw();
	// 描画後処理
	dxCommon_->PostDraw();
	// FPS固定更新
	fps_->UpdateFixFPS();
}

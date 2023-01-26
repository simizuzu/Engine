#include "Framework.h"

void Framework::Initialize()
{
	winApp_ = WinApp::GetInstance();
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstace();
	audioManager = AudioManager::GetInstance();

	// WindowsAPI初期化
	winApp_->Initialize();
	// DirectX初期化
	dxCommon_->Initialize();
	// Audio初期化
	audioManager->Initialize();
	// Input初期化
	input_->Initialize();
	// スプライト静的初期化
	Sprite::StaticInitialize();
	// FPS固定初期化
	fps_ = new FPS();
	fps_->InitializeFixFps();
}

void Framework::Finalize()
{
	audioManager->Destroy();
	// DirectX解放
	dxCommon_->Delete();
	// WindowsAPIの終了処理
	winApp_->Finalize();
	// WinApp解放
	winApp_->Delete();
	// FPS解放
	delete fps_;
}

void Framework::Update()
{
	// Windowsのメッセージ処理
	if (winApp_->ProccessMessage())
	{
		endRequest_ = true;
	}
	// 入力の更新
	input_->Update();
	audioManager->Update();
}

void Framework::Run()
{
	// ゲームの初期化
	Initialize();

	while (true) // ゲームループ
	{
		// 毎フレーム更新
		Update();
		// 終了リクエストが来たら抜ける
		if (IsEndRequest())
		{
			break;
		}
		dxCommon_->PreDraw(winApp_);
		// 描画
		Draw();
		dxCommon_->PostDraw();
		// FPS固定更新
		fps_->UpdateFixFPS();
	}
	// ゲーム終了
	Finalize();
}

bool Framework::IsEndRequest()
{
	return endRequest_;
}

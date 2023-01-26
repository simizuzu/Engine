#include "MainGame.h"

void MainGame::Initialize()
{
	// 基底クラスの初期化処理
	Framework::Initialize();


	textureManager_ = TextureManager::GetInstance();
	imGuiManager = ImGuiManager::GetInstance();


	// スプライト共通部の初期化
	textureManager_->Initialize(dxCommon_);
	// ImGui初期化
	imGuiManager->Initialize(winApp_, dxCommon_);
	
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);

	gameScene = std::make_unique<GameScene>();
	gameScene->Initialize();
}

void MainGame::Finalize()
{
	// テクスチャマネージャ解放
	textureManager_->Delete();
	// ImGui解放
	imGuiManager->Finalize();

	// 基底クラスの終了処理
	Framework::Finalize();
}

void MainGame::Update()
{
	// 基底クラスの更新処理
	Framework::Update();

	// ImGui更新処理開始
	imGuiManager->Begin();
	// ゲームシーンの毎フレーム処理
	gameScene->Update();
	// ImGui更新処理終了
	imGuiManager->End();
}

void MainGame::Draw()
{
	// ゲームシーンの描画
	gameScene->Draw();
	//ImGui描画
	imGuiManager->Draw(dxCommon_);
}

#include "MainGame.h"

void MainGame::Initialize()
{
	// 基底クラスの初期化処理
	Framework::Initialize();
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);
	//パーティクルマネージャー静的初期化
	ParticleManager::StaticInitialize(dxCommon_->GetDevice(), dxCommon_->GetCommandList());

	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);
	SceneManager::GetInstance()->ChangeScene("TITLE");
}

void MainGame::Finalize()
{
	// 基底クラスの終了処理
	Framework::Finalize();
}

void MainGame::Update()
{
	// 基底クラスの更新処理
	Framework::Update();
}

void MainGame::Draw()
{
	// ゲームシーンの描画
	//baseScene->Draw();
	sceneManager_->Draw();
}

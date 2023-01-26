#pragma once
#include "Input.h"
#include "WinApp.h"
#include "FPS.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ImGuiManager.h"
#include "GameScene.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Framework.h"

// ゲーム全体
class MainGame : public Framework
{
public: // メンバ関数
	MainGame() = default;
	~MainGame() = default;

	// 初期化
	void Initialize() override;
	// 終了
	void Finalize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// ゲーム終了フラグ
	bool endRequest_ = false;

	Sprite* sprite_ = nullptr;
	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	FPS* fps_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	AudioManager* audioManager = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	std::unique_ptr<GameScene> gameScene;
};


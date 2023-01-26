#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "FPS.h"
#include "Sprite.h"
#include "AudioManager.h"
#include "TextureManager.h"

// ゲーム全体
class Framework
{
public: // メンバ関数
	virtual ~Framework() = default;
	// 初期化
	virtual void Initialize();
	// 更新
	virtual void Finalize();
	// 毎フレーム更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest();

	// 実行
	void Run();

protected:
	// ゲーム終了フラグ
	bool endRequest_ = false;

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	AudioManager* audioManager = nullptr;
	Input* input_ = nullptr;
	FPS* fps_ = nullptr;
	TextureManager* textureManager_ = nullptr;

};


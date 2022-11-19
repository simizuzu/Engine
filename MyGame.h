#pragma once

#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Input.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "GameScene.h"

class MyGame
{
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

};


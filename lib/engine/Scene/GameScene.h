#pragma once
#include <memory>

#include "Input.h"
#include "lib/engine/Camera/Camera.h"
#include "Sprite.h"
#include "lib/engine/3D/Model/Object3d.h"
#include "lib/engine/3D/Model/Model.h"
#include "AudioManager.h"

#include "GameCollisionManager.h"

class GameScene
{
public: // メンバ関数
	// コンストラクタ
	GameScene() = default;
	// デストラクタ
	~GameScene() = default;

	//　初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();


private: // メンバ変数
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	//宣言
	INT32 sceneNum = 0;
	char PADING[4]{};

private:
	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


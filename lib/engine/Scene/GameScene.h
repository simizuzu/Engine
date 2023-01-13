#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "skydome.h"
#include "Stage.h"
#include "Player.h"

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


private: // クラス読み込み
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	std::unique_ptr<Camera> camera_;

	// スプライト
	TextureData titleTex_;
	std::unique_ptr<Sprite> titleSprite_;

	std::unique_ptr<skydome> skydome_;
	std::unique_ptr<Stage> stage_;


	uint16_t scene = 0;
private:

};


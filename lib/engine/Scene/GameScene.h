#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include"Users/Stage.h"
#include"Users/RailCamera.h"
#include"Users/ResultCamera.h"
#include"Users/ObjectManager.h"
#include"Users/Player.h"
#include"Users/skydome.h"
#include"Users/door.h"
#include"Users/SpeedUpChance.h"
#include"Users/DoorManager.h"
#include"Users/Goal.h"

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


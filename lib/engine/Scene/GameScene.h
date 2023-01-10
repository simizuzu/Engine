#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "Player.h"

class GameScene
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// コンストラクタ
	GameScene();
	// デストラクタ
	~GameScene();
	//　初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

public: // メンバ関数

private: // メンバ変数
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* object3d_ = nullptr;
	std::unique_ptr<Camera> camera_;

	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
	std::unique_ptr<Model> model_;

	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> playerModel_;


	// サウンド
	uint32_t gameHandle = 0;

	// シーン

	enum Scene {
		title,
		appear,
		game,
		defeat,
		gameover,
		clear
	};

	//シーン
	Scene scene = title;
};


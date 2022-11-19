#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"

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
	Camera* viewProjection_ = nullptr;

	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* object3d_ = nullptr;

	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
};


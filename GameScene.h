#pragma once
#include "Sprite.h"
#include <memory>

class GameScene
{
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
	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
};


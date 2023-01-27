#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"
#include "BaseScene.h"
#include "TextureManager.h"
#include "SceneManager.h"

#include "GameCollisionManager.h"

class GameScene : public BaseScene
{
public: // メンバ関数
	// コンストラクタ
	GameScene() = default;
	// デストラクタ
	~GameScene() = default;

	//　初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// 終了処理
	void Finalize() override;


private: // メンバ変数
	Input* input_ = nullptr;
	std::unique_ptr<Camera> camera;
	DirectXCommon* dxCommon_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	TextureData tex;
	std::unique_ptr<Sprite> sprite_;

	//宣言
	INT32 sceneNum = 0;
	char PADING[4]{};

	// ImGuiデバック用
	float pos[2] = {100,100};

private:
	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


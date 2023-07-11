﻿#pragma once
#include <memory>
#include "BaseScene.h"
#include "SceneManager.h"

#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ObjModel.h"
#include "AudioManager.h"

#include "TextureManager.h"
#include "WorldTransform.h"

#include "GameCamera.h"

#pragma warning(push)
#pragma warning(disable: 4091)
#pragma warning(pop)

class GameScene : public BaseScene
{
public: // メンバ関数
	GameScene() = default;
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
	std::unique_ptr<Light> light;
	//AudioManager* audioManager_ = nullptr;

	std::unique_ptr<GameCamera> gameCamera;

	SceneManager* sceneManager_ = nullptr;

	//宣言
	INT32 sceneNum = 0;
	char PADING[4]{};

	// サウンド
	//uint32_t gameHandle_ = 0;

	std::unique_ptr<Object3d> skydomeObj_;
	std::unique_ptr<ObjModel> skydomeModel_;

	MyMath::Vector3 cameraRot = {0,0,0};
	MyMath::Vector3 cameraTarget;

	WorldTransform skydomeTrans;

private:
	//コピーコンストラクタ・代入演算子削除

	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


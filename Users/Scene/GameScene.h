#pragma once
#include <memory>
#include <map>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"
#include "BaseScene.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "TitleScene.h"

#include "LevelLoader.h"

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
	DirectXCommon* dxCommon_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	SceneManager* sceneManager_ = nullptr;

	std::unique_ptr<Object3d> objCylinder;
	std::unique_ptr<Object3d> objCube;
	std::unique_ptr<Model> cylinder;
	std::unique_ptr<Model> cube;

	//宣言
	INT32 sceneNum = 0;
	char PADING[4]{};

	// ImGuiデバック用
	Mathematics::Vector2 pos = {100,100};
	
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	LevelData* levelData = nullptr;
	std::map<std::string, Model*> models;

	// サウンド
	uint32_t gameHandle_ = 0;
	std::vector<Object3d*> objects;

private:
	//コピーコンストラクタ・代入演算子削除

	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


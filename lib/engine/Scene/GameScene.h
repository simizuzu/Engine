#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Object3d.h"
#include "Model.h"

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
	~GameScene();
	//　初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();


private: // クラス読み込み
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Camera* camera_ = nullptr;

	// スプライト
	TextureData titleTex_;
	std::unique_ptr<Sprite> titleSprite_;

	// クラス
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<ResultCamera> resultCamera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<skydome> skydome_;
	std::unique_ptr<ObjectManager> objectManager_;
	std::unique_ptr<SpeedUpChance>speedUpChance_;
	std::unique_ptr<DoorManager> doorManager_;
	std::unique_ptr<Goal> goalModel_;

	enum class Scene
	{
		title,
		game,
		door,
		result
	};

	Scene scene = Scene::title;

	int startTime = 0;

	int nowTime = 0;

	int endTime = 0;

	int frequencyInvocationDoor = 0;

	//発動中？
	bool isActivationDoor = false;

	bool titleParticleFrg = false;
	bool ParticleFrg = false;
	bool resultParticleFrg = false;

	bool startGameFrg = false;

	bool endGameFrg = false;

private:

};


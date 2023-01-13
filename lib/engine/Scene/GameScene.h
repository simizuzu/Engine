#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Radar.h"
#include "GameCollisionConflg.h"

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

	//ゲッター
	static GameScene* GetInstance();
	int GetSceneNum();
	void SetSceneNum(int sceneNum);

	void Collision();

	void Reset();

private: // メンバ変数
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* object3d_ = nullptr;
	std::unique_ptr<Camera> camera_;
	AudioManager* audioManager_ = nullptr;

	uint32_t gameScene = 0;
	uint32_t titleScene = 0;
	uint32_t gameClearScene = 0;


	std::unique_ptr<Sprite> titleBack;
	TextureData titleTex{};
	Object3d titleTrans{};

	std::unique_ptr<Sprite> gameClear;
	TextureData gameClearTex{};
	Object3d gameClearTrans{};

	std::unique_ptr<Sprite> gameOver;
	TextureData gameOverTex{};
	Object3d gameOverTrans{};

	//モデル
	EnemyData enemyData;
	RadarData radarData;
	PlayerData playerData;

	std::unique_ptr<Model>skydome;
	Object3d skydomeTransform;
	std::unique_ptr<Model>ground;
	Object3d groundTransform;

	std::shared_ptr<Player>player_;

	std::unique_ptr<GameCollisionManager> collisionManager_;

	std::vector<Mathematics::Vector3> controlPoints_ = {
	{0.0f,1000.0f,1000.0f   },
	{500.0f,1000.0f,500.0f  },
	{1000.0f,1000.0f,0.0f   },
	{500.0f,1000.0f,-500.0f },
	{0.0f,1000.0f,-1000.0f  },
	{-500.0f,1000.0f,-500.0f},
	{-1000.0f,1000.0f,0.0f  },
	{-500.0f,1000.0f,500.0f },
	{0.0f,1000.0f,1000.0f   }
	};

	//sano
	std::vector<Mathematics::Vector3>enemy1 = {
		{0.0f,4000.0f,0.0f },//真ん中
		{-2000.0f,4000.0f,-4000.0f },//左下
		{0.0f,4000.0f,-8000.0f },//下
		{2000.0f,4000.0f,-4000.0f },//右下
		{0.0f,4000.0f,0.0f },//真ん中
		{-2000.0f,4000.0f,4000.0f },//左上
		{0.0f,4000.0f,8000.0f },//上
		{2000.0f,4000.0f,4000.0f },//右上
		{0.0f,4000.0f,0.0f },//真ん中
	};

	std::vector<Mathematics::Vector3>enemy2 = {//左上から
		{ 6000.0f,4000.0f, 6000.0f},
		{    0.0f,4000.0f,    0.0f},
		{-6000.0f,4000.0f,-6000.0f},
		{    0.0f,4000.0f,-6000.0f},
		{ 6000.0f,4000.0f,-6000.0f},
		{ 6000.0f,4000.0f,-2000.0f},
		{ 6000.0f,4000.0f, 6000.0f},
	};

	std::vector<Mathematics::Vector3>enemy3 = {//右上から
		{-6000.0f,4000.0f, 6000.0f},
		{    0.0f,4000.0f,    0.0f},
		{ 6000.0f,4000.0f,-6000.0f},
		{ 6000.0f,4000.0f,-2000.0f},
		{ 6000.0f,4000.0f, 2000.0f},
		{ 6000.0f,4000.0f, 6000.0f},
		{-6000.0f,4000.0f, 6000.0f},
	};

	std::vector<Mathematics::Vector3>enemy4 = {//右下から
		{-6000.0f,4000.0f,-6000.0f},
		{    0.0f,4000.0f,    0.0f},
		{ 6000.0f,4000.0f, 6000.0f},
		{    0.0f,4000.0f, 6000.0f},
		{-6000.0f,4000.0f, 6000.0f},
		{-6000.0f,4000.0f, 2000.0f},
		{-6000.0f,4000.0f,-6000.0f},
	};

	std::vector<Mathematics::Vector3>enemy5 = {//左下から
		{ 6000.0f,4000.0f,-6000.0f},
		{    0.0f,4000.0f,    0.0f},
		{-6000.0f,4000.0f, 6000.0f},
		{-6000.0f,4000.0f, 2000.0f},
		{-6000.0f,4000.0f,-2000.0f},
		{-6000.0f,4000.0f,-6000.0f},
		{ 6000.0f,4000.0f,-6000.0f},
	};

	std::list<std::shared_ptr<Enemy>>enemys_;

	std::shared_ptr<GameCamera> gameCamera;

	Radar* radar_ = nullptr;
	//宣言
	INT32 sceneNum = 0;
	char PADING[4]{};

	INT32 destroyFlag = 0;

private:
	//コピーコンストラクタ・代入演算子削除
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


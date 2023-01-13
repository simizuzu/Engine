#pragma once
#include <memory>
#include <list>

#include "Model.h"
#include "Input.h"
#include "Object3d.h"
#include "GameCamera.h"
#include "WinApp.h"
#include "GameCollisionConflg.h"
#include "AudioManager.h"
#include "CollisionPrimitive.h"
#include "Sprite.h"

class Enemy;

struct PlayerData
{
	std::shared_ptr<Model> playerModel_;
	std::shared_ptr<GameCamera> camera_;
	TextureData sceneChangeTex;
	TextureData silenPullUpTex;
	TextureData silenReturnTex;

	uint32_t fighterSE = 0;
};

class Player : BoundingBox
{
public:
	Player() = default;
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Mathematics::Vector3 pos, PlayerData data);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera,INT32& sceneNum);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの挙動
	/// </summary>
	void PlayerMove(INT32& sceneNum);
	void Rotate();
	// 移動補完
	void Complement(float& x1, float x2, float flame);

	/// <summary>
	/// 当たった判定
	/// </summary>
	virtual void OnCollision()override;

	// ゲッター
	Object3d* GetTransform();
	Mathematics::Vector3 GetWorldPosition();

private:
	Input* input_ = nullptr;

	// プレイヤーの座標
	Mathematics::Vector3 playerPos;

	// プレイヤーのモデル
	std::shared_ptr<Model> playerModel_;	
	std::unique_ptr < Object3d> playerObject_;

	std::unique_ptr<Object3d> transform_{};
	
	// カメラ
	std::shared_ptr<GameCamera> camera_;

	std::unique_ptr<Sprite>silenPullUp;
	TextureData silenPullUpTex_{};
	Object3d silenPullUpTransform;

	std::unique_ptr<Sprite>silenReturn;
	TextureData silenReturnTex_{};
	Object3d silenReturnTransform;

	

private:
	float speed_ = 600.0f;
	float alpha = 0.0f;
	bool initflag = true;
	bool animationFlag = false;

	Mathematics::Vector3 oldTranslation_;

	int32_t hp = 4;
	uint32_t fighterSE = 0;
};


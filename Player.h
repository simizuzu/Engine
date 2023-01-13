#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Camera.h"
#include "Input.h"
#include "CollisionPrimitive.h"
#include "AudioManager.h"

class Player
{
	// コンストラクタ・デストラクタ
	Player();
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Object3d* trans);

	/// <summary>
	/// ゲーム中の毎フレーム処理
	/// </summary>
	void Update();
	/// <summary>
	/// ゲーム以外の毎フレーム処理
	/// </summary>
	void titleUpdate();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	Object3d& GetWorldTransform();

	AABB& GetCollider();

	void OnCollision();

	bool GetCrashFlag();

	void SetTransform(Mathematics::Vector3 position);

	void EndGameReset();

	void JumpReset();

private:
	void Move();
	void Rotate();
	void Complement(float& x1, float x2, float flame);
	void Jump();
	void Squat();

	uint8_t jumpFlag = 0u;
	
	float gravitySpeed = 0.5f;
	float defGravitySpeed = gravitySpeed;

	bool crashFlag = false;

	uint32_t crashTime = 70;
	AABB collider_;

	//回転運動を止める
	bool rollStopFlag = false;

	//しゃがみフラグ
	bool squatFlag = false;

	Mathematics::Vector3 oldRot;
	uint32_t squatTime = 60 * 2;
	float oldRotY = 0.0f;

	//モデル
	std::shared_ptr<Model> model_;
	// ワールドトランスフォーム
	std::shared_ptr<Object3d> worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	Player& operator=(const Player&) = delete;
	Player(const Player&) = delete;

	//サウンド
	uint32_t confusionHandle = 0;
};


#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Model.h"
#include "GameCamera.h"
#include "CollisionPrimitive.h"
#include "Sprite.h"
#include "GameCollisionConflg.h"
#include "GameScene.h"
#include "DirectX12Math.h"

enum class Phase
{
	Approach,	// 接近する
	Around,		// 周回する
};

class GameScene;
class Player;

struct EnemyData
{
	// モデル
	std::shared_ptr<Model> enemyModel_;
	// カメラ
	std::shared_ptr<GameCamera> camera_;
	// プレイヤー
	std::shared_ptr<Player> player_;
};

class Enemy : public BoundingBox
{
private:
	GameScene* gamescene_ = nullptr;

	// モデル
	std::shared_ptr<Model> enemymodel_;
	std::shared_ptr<Object3d> enemyObject_;
	// カメラ
	std::shared_ptr<GameCamera> camera_;
	// プレイヤー
	std::shared_ptr<Player>player_;

	// 座標変換
	Object3d transform_;

	// 制御点
	std::vector<Mathematics::Vector3> controlPoints_;
	Mathematics::Vector3 initpos;

	float time = 0.0f;

	Phase phase = Phase::Approach;

	int32_t hitTimer = 0;
	Mathematics::Vector3 targetVec_;
	float targetSize_ = 0.0f;
	Mathematics::Vector3 velocity_;
	int32_t attackInterval = 60 * 5;
	bool isRockOnFlag = false;
	int32_t hp = 6;
	bool isDead = false;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(EnemyData& data, Mathematics::Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetControlPoint(std::vector<Mathematics::Vector3>& controlPoints);

	Mathematics::Vector3 GetWorldPosition();

	void SetRockOn(bool flag);

	bool GetRockOn();

	Object3d& GetTransform();

	virtual void OnCollision();

	bool IsDead() const;//デスフラグゲッター

	Enemy() = default;
	~Enemy() = default;

private:
	//接近フェーズ
	void ApproachMove();

	//周回フェーズ
	void AroundMove();

	void Attack();

	bool AttackFlag();

	void HitUpdate();

	//コピーコンストラクタ・代入演算子削除
	Enemy& operator=(const Enemy&) = delete;
	Enemy(const Enemy&) = delete;
};


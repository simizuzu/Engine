#pragma once
#include <memory>
#include <list>

#include "Model.h"
#include "Input.h"
#include "Object3d.h"
#include "Camera.h"


class Player
{
public:
	Player() = default;
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(std::unique_ptr<Model>& model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	/// <summary>
	/// プレイヤーの挙動
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// 弾の挙動
	/// </summary>
	void BulletShot();

private:
	// プレイヤーの座標
	Mathematics::Vector3 playerPos;
	// 弾の座標
	Mathematics::Vector3 bulletPos;

	// プレイヤーのモデル
	std::unique_ptr<Model> playerModel_;
	std::unique_ptr<Model> bulletModel_ = nullptr;
	
	std::unique_ptr < Object3d> playerObject_ = nullptr;
	std::unique_ptr < Object3d> bulletObject_ = nullptr;

	// 入力
	Input* input_ = nullptr;
};


#pragma once
#include <memory>
#include "Model.h"
#include "Input.h"
#include "Object3d.h"
#include "Camera.h"

class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

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

	void BulletShot();

private:
	// プレイヤーの座標
	Mathematics::Vector3 playerPos;
	// プレイヤーのモデル
	Model* playerModel_ = nullptr;
	Model* bulletModel_ = nullptr;
	// 入力
	Input* input_ = nullptr;
	
	Object3d* playerObject_ = nullptr;
};


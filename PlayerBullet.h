#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	
	std::unique_ptr<Model> bulletModel_;
	std::unique_ptr<Object3d> bulletObject_;
};


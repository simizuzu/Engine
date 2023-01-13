#pragma once

#include "Input.h"
#include "lib/engine/3D/Model/Object3d.h"
#include"DirectX12Math.h"
#include "lib/engine/3D/Model/Model.h"


class door
{
public:

	door();

	~door();

	// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Mathematics::Vector3 trans, Mathematics::Vector3 Rot);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Mathematics::Vector3 vector);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	bool GetMashFlag();

	void Reset(Mathematics::Vector3 trans);

	UINT GetMashNum();

private:

	//連打処理
	void Mash(Mathematics::Vector3 vector);

	bool mashFlag_ = false;
	char PADING[3]{};
	UINT mashNum_ = 0;

	std::unique_ptr<Object3d> door1worldTransform_;
	std::unique_ptr<Object3d> door2worldTransform_;
	std::unique_ptr<Object3d> door3worldTransform_;

	std::unique_ptr<Model> door1model_;
	std::unique_ptr<Model> door2model_;
	std::unique_ptr<Model> door3model_;

	Input* input_ = nullptr;

	//コピーコンストラクタ・代入演算子削除
	door& operator=(const door&) = delete;
	door(const door&) = delete;
};


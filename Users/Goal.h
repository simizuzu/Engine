#pragma once
#include "lib/engine/3D/Model/Object3d.h"
#include "lib/engine/Camera/Camera.h"
#include "lib/engine/3D/Model/Model.h"

#include <memory>

class Goal
{
public:

	Goal() = default;
	~Goal() = default;

	// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

private:
	std::unique_ptr<Model> model_;
	std::unique_ptr<Object3d> worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	Goal& operator=(const Goal&) = delete;
	Goal(const Goal&) = delete;
};
#pragma once
#include <memory>

#include "Input.h"
#include "Object3d.h"
#include "Camera.h"

class Stage
{
public:
	// コンストラクタ・デストラクタ
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ワールドトランスフォーム
	std::shared_ptr<Object3d> WorldTransform_;
	std::shared_ptr<Model> model_;
	
	Mathematics::Vector3 vector_ = {};

	//コピーコンストラクタ・代入演算子削除
	Stage& operator=(const Stage&) = delete;
	Stage(const Stage&) = delete;
};


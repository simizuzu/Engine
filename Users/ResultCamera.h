#pragma once

#include "Camera.h"
#include "Object3d.h"

class ResultCamera
{
public:

	ResultCamera();
	~ResultCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Object3d* worldTransform);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Camera* GetViewProjection();

	Object3d* GetWorldTransformPtr();

	void addRot(Mathematics::Vector3 rot);
	void addTranslation(Mathematics::Vector3 translation);

	void setTranslation(Mathematics::Vector3 translation);

private:

	Camera* viewProjection_ = nullptr;

	std::unique_ptr<Object3d>worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	ResultCamera& operator=(const ResultCamera&) = delete;
	ResultCamera(const ResultCamera&) = delete;
};

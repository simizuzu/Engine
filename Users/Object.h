#pragma once
#include"lib/engine/3D/Model/Model.h"
#include"lib/engine/3D/Model/Object3d.h"
#include"lib/engine/Camera/Camera.h"
#include"CollisionPrimitive.h"

class Object
{
public:

	Object() = default;
	~Object() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, float radius, Model* model);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

	//コライダー所得
	Sphere& GetCollider();

	//当たった時の関数
	void OnCollision();

	bool GetIsDeath();

private:
	bool IsDeath;
	char PADING[3]{};
	Sphere collider_;
	char PADING2[4]{};
	Model* model_;
	std::unique_ptr<Object3d> worldTransform_;

	//コピーコンストラクタ・代入演算子削除
	Object& operator=(const Object&) = delete;
	Object(const Object&) = delete;
};
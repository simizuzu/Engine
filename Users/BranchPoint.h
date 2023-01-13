#pragma once
#include"lib/engine/3D/Model/Model.h"
#include"RailCamera.h"
#include"Player.h"
#include"lib/engine/Camera/Camera.h"
class BranchPoint
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, const Mathematics::Vector3& size, Model* bodyModel, std::function<void(void)>left, std::function<void(void)>right);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

private:
	//本体
	Model* bodyModel_ = nullptr;
	std::unique_ptr<Object3d> bodyWorldTransform_;

	AABB collider_;

	std::function<void()>left_;
	std::function<void()>right_;

	bool passingFlag_ = false;

	std::unique_ptr<BoundingBox> boundingBox_;

	char PADING[7]{};
};


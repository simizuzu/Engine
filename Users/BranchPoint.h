#pragma once
#include"lib/engine/3D/Model/Model.h"
#include"RailCamera.h"
#include"Player.h"
#include"lib/engine/Camera/Camera.h"
class BranchPoint
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, const Mathematics::Vector3& size, Model* bodyModel, std::function<void(void)>left, std::function<void(void)>right);

	/// <summary>
	/// –ˆƒtƒŒ[ƒ€ˆ—
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(Camera* camera);

private:
	//–{‘Ì
	Model* bodyModel_ = nullptr;
	std::unique_ptr<Object3d> bodyWorldTransform_;

	AABB collider_;

	std::function<void()>left_;
	std::function<void()>right_;

	bool passingFlag_ = false;

	std::unique_ptr<BoundingBox> boundingBox_;

	char PADING[7]{};
};


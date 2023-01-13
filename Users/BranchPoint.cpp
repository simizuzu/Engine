#include "BranchPoint.h"
#include"Collision.h"

void BranchPoint::Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, const Mathematics::Vector3& size, Model* bodyModel, std::function<void(void)>left, std::function<void(void)>right)
{
	bodyModel_ = bodyModel;
	bodyWorldTransform_->SetModel(bodyModel_);
	bodyWorldTransform_.reset(Object3d::Create());
	bodyWorldTransform_->position = pos;
	bodyWorldTransform_->scale = { 12.0f,12.0f,12.0f };
	bodyWorldTransform_->rotation = rot;
	bodyWorldTransform_->matWorld = Mathematics::MakeWorldMatrix4(*bodyWorldTransform_);

	collider_.center = Mathematics::GetWorldPosition(*bodyWorldTransform_);
	collider_.size = {
		size.x* bodyWorldTransform_->scale.x,
		size.y* bodyWorldTransform_->scale.y,
		size.z* bodyWorldTransform_->scale.z };

	left_ = left;
	right_ = right;

	boundingBox_ = std::make_unique<BoundingBox>();
}

void BranchPoint::Update(Player* player)
{
	if (!passingFlag_&& boundingBox_->CheckAABBToAABB(player->GetCollider(), collider_))
	{
		passingFlag_ = true;

		if (player->GetWorldTransform().position.x > 0)
		{
			left_();
		}
		else
		{
			right_();
		}
	}
}

void BranchPoint::Draw(Camera* camera)
{
	bodyWorldTransform_->Update(camera);
	bodyWorldTransform_->Draw();

}
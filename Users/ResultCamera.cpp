#include "ResultCamera.h"

ResultCamera::ResultCamera()
{
}

ResultCamera::~ResultCamera()
{
}

void ResultCamera::Initialize(Object3d* worldTransform)
{
	worldTransform_.reset(Object3d::Create());
	worldTransform_->parent = worldTransform;

	//ワールドトランスフォームの初期設定
	worldTransform_->position = {2.0f,-2.0f,11.5f};
	worldTransform_->rotation = { 0.0,250.0f * MyMathUtility::degree2Radius,0.0f };

	viewProjection_ = new Camera();
	viewProjection_->SetFarZ(12000.0f);
	//ビュープロジェクションの初期化
	viewProjection_->Initialize();
}

void ResultCamera::Update()
{

	Mathematics::MakeWorldMatrix4(*worldTransform_);

	viewProjection_->eye_ = Mathematics::GetWorldPosition(*worldTransform_);
	//ワールド前方ベクトル
	Mathematics::Vector3 forward(0, 0, 1);
	//レールカメラの回転を反映
	forward = Mathematics::Vec3Mat4Mul(forward, worldTransform_->matWorld);
	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_->target_ = viewProjection_->eye_ + forward;
	//ワールド上方ベクトル
	Mathematics::Vector3 up(0, 1, 0);
	//レールカメラの回転を反映(レールカメラの上方ベクトル)
	viewProjection_->up_ = Mathematics::Vec3Mat4Mul(up, worldTransform_->matWorld);
}

void ResultCamera::Draw() {}

Camera* ResultCamera::GetViewProjection()
{
	return viewProjection_;
}

Object3d* ResultCamera::GetWorldTransformPtr()
{
	return worldTransform_.get();
}
void ResultCamera::addTranslation(Mathematics::Vector3 translation)
{
	worldTransform_->position += translation;
}
void ResultCamera::addRot(Mathematics::Vector3 rot)
{
	worldTransform_->rotation += rot;
}
void ResultCamera::setTranslation(Mathematics::Vector3 translation)
{
	worldTransform_->position = translation;
}
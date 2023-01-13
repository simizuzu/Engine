#include "Player.h"
#include <cassert>

void Player::Initialize()
{
	// シングルトン
	input_ = Input::GetInstace();

	playerModel_.reset(Model::LoadFromObj("Tyoinori"));
	playerObject_.reset(Object3d::Create());
	playerObject_->SetModel(playerModel_.get());

	transform_ = std::make_unique<Object3d>();
	transform_->Initialize();
	transform_->parent = camera_->GetTransform();
	transform_->position = { 0.0f, -18.0f, 30.0f };
	transform_->scale = { 10.0f,10.0f,10.0f };

	CreateOBB(playerModel_->GetVertices(), *transform_);

	// 衝突属性を設定
	SetCollisionAttribute(CollisionAttributePlayer);
	//衝突対象を自分以外に設定
	SetCollisionMask(~CollisionAttributePlayer);

	collsionName_ = "Player";

	trans.Create();
}

void Player::Update(Camera* camera, INT32& sceneNum)
{
	// 行列を転送
	playerObject_->Update(camera);

	oldTranslation_ = GetWorldPosition();

	PlayerMove(sceneNum);
	Rotate();
	transform_->Update(camera_->GetCamera());

	UpdateOBB(*transform_);

	//体力が0以下になったら
	if (hp <= 0)
	{
		//ゲームオーバーシーン
		if (animationFlag == false)
		{

		}
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 60;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			sceneNum = 2;
		}
	}

	worldPos_ = camera_->GetWorldPosition();
	velocity_ = { 0, 0, 5000.0f };
	tmp = velocity_ = Mathematics::Vec3Mat4Mul(velocity_, camera_->GetTransform()->matWorld);

	trans.position = worldPos_;
	trans.Update(camera_->GetCamera());

	//終了処理
	if (GetWorldPosition().x <= -11600 || GetWorldPosition().x >= 11600 || GetWorldPosition().z <= -11600 || GetWorldPosition().z >= 11600)
	{
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 100;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			sceneNum = 2;
		}
	}

	if (GetWorldPosition().y >= 11600 || GetWorldPosition().y <= 0)
	{
		animationFlag = true;
		if (animationFlag == true)
		{
			alpha += 1.0f / 60;
		}

		if (alpha >= 1.0f)
		{
			animationFlag = false;
			sceneNum = 2;
		}
	}

	if (damageFlag == true)
	{
		damageAlpha -= 0.5f / 60;
		if (damageAlpha <= 0)
		{
			damageFlag = false;
		}
	}
	else
	{
		damageAlpha = 0.5f;
	}
}

void Player::Draw()
{
	playerObject_->Draw();
	

	/*if (animationFlag == true)
	{
		sceneChange->Draw(sceneChangeTex_);
	}*/

	worldPos_ = worldPos_ + tmp;
}

void Player::PlayerMove(INT32& sceneNum)
{
	//横移動
	//コントローラー操作
	Complement(transform_->position.x, -input_->GetLeftStickVec({ 1.0f,1.0f }).x * 30, 40);
	//キーボード操作
	Complement(transform_->position.x, input_->GetKeyTime(DIK_A) / 254.0f * 30, 40);
	Complement(transform_->position.x, -input_->GetKeyTime(DIK_D) / 254.0f * 30, 40);
}

void Player::Rotate()
{
	//旋回処理
	//コントローラー操作
	Complement(transform_->rotation.z, -input_->GetLeftStickVec({ 1.0f,1.0f }).x * 40.0f * MyMathUtility::degree2Radius, 40);//横
	//キーボード操作
	Complement(transform_->rotation.z, input_->GetKeyTime(DIK_A) / 254.0f * 40.0f * MyMathUtility::degree2Radius, 40);
	Complement(transform_->rotation.z, -input_->GetKeyTime(DIK_D) / 254.0f * 40.0f * MyMathUtility::degree2Radius, 40);
}

void Player::Complement(float& x1, float x2, float flame)
{
	MyMathUtility::Complement(x1, x2, flame);
}

void Player::OnCollision()
{
}

Object3d* Player::GetTransform()
{
	return transform_.get();
}

Mathematics::Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Mathematics::Vector3 worldPos;
	//ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = transform_->matWorld.m[3][0];
	worldPos.y = transform_->matWorld.m[3][1];
	worldPos.z = transform_->matWorld.m[3][2];

	return worldPos;
}

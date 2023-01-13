#include "Enemy.h"

void Enemy::Initialize(EnemyData& data, Mathematics::Vector3& position)
{
	gamescene_ = GameScene::GetInstance();

	enemymodel_ = data.enemyModel_;
	camera_ = data.camera_;
	player_ = data.player_;

	transform_.Create();
	transform_.position = position;
	initpos = position;
	transform_.scale = { 3.0f,3.0f,3.0f };

	CreateOBB(enemymodel_->GetVertices(), transform_);
	transform_.SetModel(enemymodel_.get());

	// 衝突属性を設定
	SetCollisionAttribute(CollisionAttributeEnemy);
	// 衝突対象を自分以外に設定
	SetCollisionMask(~CollisionAttributeEnemy);
	collsionName_ = "Enemy";
}

void Enemy::Update()
{
	switch (phase)
	{
	case Phase::Approach://接近フェーズ
		ApproachMove();
		break;
	case Phase::Around://周回フェーズ
		AroundMove();
		break;
	default:
		break;
	}

	transform_.Update(camera_->GetThirdPersonCamera());

	if (attackInterval > 0)
	{
		attackInterval--;
	}

	printf("Hp:::%d\n", hp);

	UpdateOBB(transform_);

	if (hp <= 0 && hitTimer == 0)
	{
		isDead = true;
	}
}

void Enemy::Draw()
{
	//描画
	transform_.Draw();
}

void Enemy::SetControlPoint(std::vector<Mathematics::Vector3>& controlPoints)
{
	controlPoints_ = controlPoints;
}

Mathematics::Vector3 Enemy::GetWorldPosition()
{
	return Mathematics::GetWorldPosition(transform_);
}

void Enemy::SetRockOn(bool flag)
{
	isRockOnFlag = flag;
}

bool Enemy::GetRockOn()
{
	return isRockOnFlag;
}

Object3d& Enemy::GetTransform()
{
	return transform_;
}

void Enemy::OnCollision()
{
	if (GetOppCollsionName() == "Player")
	{
		hp = 0;
	}
}

bool Enemy::IsDead() const
{
	return isDead;
}

void Enemy::ApproachMove()
{
	time += 0.001f;
	time = MyMathUtility::Clamp0To1(time);

	Mathematics::Vector3 tmpvec = transform_.position;

	//初期値から制御点の最初の所へ移動
	transform_.position = MyMathUtility::Lerp(initpos, controlPoints_[0], time);

	if (time >= 1.0f)
	{
		//周回フェーズに移動
		phase = Phase::Around;
		time = 0.0f;
	}

	//方向ベクトル計算
	velocity_ = transform_.position - tmpvec;

	Mathematics::Vector3 temp = velocity_;
	temp.y = 0.0f;

	//ヨー計算
	transform_.rotation.y = MyMathUtility::Atan2(velocity_.x, velocity_.z);
	//ピッチ計算
	transform_.rotation.x = MyMathUtility::Atan2(-velocity_.y, temp.length());
}

void Enemy::AroundMove()
{
	time += 0.001f;
	time = MyMathUtility::Clamp0To1(time);

	//キャットムルスプライン曲線
	transform_.position = Mathematics::CatMullRomSpline(controlPoints_, time);

	if (time >= 1.0f)
	{
		time = 0.0f;
	}

	float tmpTime = time + 0.002f;
	tmpTime = MyMathUtility::Clamp0To1(tmpTime);

	//方向ベクトル計算
	velocity_ = Mathematics::CatMullRomSpline(controlPoints_, tmpTime) - Mathematics::CatMullRomSpline(controlPoints_, time);
	Mathematics::Vector3 temp = velocity_;
	temp.y = 0.0f;

	//ヨー計算
	transform_.rotation.y = MyMathUtility::Atan2(velocity_.x, velocity_.z);
	//ピッチ計算
	transform_.rotation.x = MyMathUtility::Atan2(-velocity_.y, temp.length());
}

void Enemy::Attack()
{
}

bool Enemy::AttackFlag()
{
	return false;
}

void Enemy::HitUpdate()
{
}

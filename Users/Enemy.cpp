#include "Enemy.h"

void Enemy::Initialize()
{
	gamescene_ = GameScene::GetInstance();

	enemyModel_ = std::make_unique<Model>();
	enemyModel_.reset(Model::LoadFromObj("ring"));

	camera_ = std::make_unique<GameCamera>();
	camera_->Initialize();
	player_ = std::make_unique<Player>();

	Mathematics::Vector3 position = { -12000.0f,4000.0f,12000.0f };

	transform_.Create();
	transform_.SetModel(enemyModel_.get());
	transform_.position = position;
	initpos = position;
	transform_.scale = { 3.0f,3.0f,3.0f };

	CreateOBB(enemyModel_->GetVertices(), transform_);
	transform_.SetModel(enemyModel_.get());

	// �Փˑ�����ݒ�
	SetCollisionAttribute(CollisionAttributeEnemy);
	// �ՓˑΏۂ������ȊO�ɐݒ�
	SetCollisionMask(~CollisionAttributeEnemy);
	collsionName_ = "Enemy";
}

void Enemy::Update()
{
	switch (phase)
	{
	case Phase::Approach://�ڋ߃t�F�[�Y
		ApproachMove();
		break;
	case Phase::Around://����t�F�[�Y
		AroundMove();
		break;
	default:
		break;
	}

	transform_.Update(camera_->GetCamera());

	if (attackInterval > 0)
	{
		attackInterval--;
	}

	UpdateOBB(transform_);

	if (hp <= 0 && hitTimer == 0)
	{
		isDead = true;
	}
}

void Enemy::Draw()
{
	//�`��
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

	//�����l���琧��_�̍ŏ��̏��ֈړ�
	transform_.position = MyMathUtility::Lerp(initpos, controlPoints_[0], time);

	if (time >= 1.0f)
	{
		//����t�F�[�Y�Ɉړ�
		phase = Phase::Around;
		time = 0.0f;
	}

	//�����x�N�g���v�Z
	velocity_ = transform_.position - tmpvec;

	Mathematics::Vector3 temp = velocity_;
	temp.y = 0.0f;

	//���[�v�Z
	transform_.rotation.y = MyMathUtility::Atan2(velocity_.x, velocity_.z);
	//�s�b�`�v�Z
	transform_.rotation.x = MyMathUtility::Atan2(-velocity_.y, temp.length());
}

void Enemy::AroundMove()
{
	time += 0.001f;
	time = MyMathUtility::Clamp0To1(time);

	//�L���b�g�����X�v���C���Ȑ�
	transform_.position = Mathematics::CatMullRomSpline(controlPoints_, time);

	if (time >= 1.0f)
	{
		time = 0.0f;
	}

	float tmpTime = time + 0.002f;
	tmpTime = MyMathUtility::Clamp0To1(tmpTime);

	//�����x�N�g���v�Z
	velocity_ = Mathematics::CatMullRomSpline(controlPoints_, tmpTime) - Mathematics::CatMullRomSpline(controlPoints_, time);
	Mathematics::Vector3 temp = velocity_;
	temp.y = 0.0f;

	//���[�v�Z
	transform_.rotation.y = MyMathUtility::Atan2(velocity_.x, velocity_.z);
	//�s�b�`�v�Z
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

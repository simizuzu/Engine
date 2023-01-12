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

	transform_.Update(camera_->GetThirdPersonCamera());

	if (attackInterval > 0)
	{
		attackInterval--;
	}

	printf("Hp:::%d\n", hp);

	UpdateOBB(transform_);

	if (hp <= 0 && hitTimer == 29)
	{
		AudioManager::GetInstance()->PlayWave(destroySE);

	}
	if (hp <= 0 && hitTimer == 0)
	{
		isDead = true;
	}
}

void Enemy::Draw()
{
}

void Enemy::SetControlPoint(std::vector<Mathematics::Vector3>& controlPoints)
{
}

Mathematics::Vector3 Enemy::GetWorldPosition()
{
	return Mathematics::Vector3();
}

void Enemy::SetRockOn(bool flag)
{
}

bool Enemy::GetRockOn()
{
	return false;
}

Object3d& Enemy::GetTransform()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

void Enemy::OnCollision()
{
}

bool Enemy::IsDead() const
{
	return false;
}

void Enemy::ApproachMove()
{
}

void Enemy::AroundMove()
{
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

#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Model.h"
#include "GameCamera.h"
#include "CollisionPrimitive.h"
#include "Sprite.h"
#include "GameCollisionConflg.h"
#include "GameScene.h"
#include "DirectX12Math.h"

enum class Phase
{
	Approach,	// �ڋ߂���
	Around,		// ���񂷂�
};

class GameScene;
class Player;

struct EnemyData
{
	// ���f��
	std::shared_ptr<Model> enemyModel_;
	// �J����
	std::shared_ptr<GameCamera> camera_;
	// �v���C���[
	std::shared_ptr<Player> player_;
};

class Enemy : public BoundingBox
{
private:
	GameScene* gamescene_ = nullptr;

	// ���f��
	std::shared_ptr<Model> enemymodel_;
	std::shared_ptr<Object3d> enemyObject_;
	// �J����
	std::shared_ptr<GameCamera> camera_;
	// �v���C���[
	std::shared_ptr<Player>player_;

	// ���W�ϊ�
	Object3d transform_;

	// ����_
	std::vector<Mathematics::Vector3> controlPoints_;
	Mathematics::Vector3 initpos;

	float time = 0.0f;

	Phase phase = Phase::Approach;

	int32_t hitTimer = 0;
	Mathematics::Vector3 targetVec_;
	float targetSize_ = 0.0f;
	Mathematics::Vector3 velocity_;
	int32_t attackInterval = 60 * 5;
	bool isRockOnFlag = false;
	int32_t hp = 6;
	bool isDead = false;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(EnemyData& data, Mathematics::Vector3& position);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void SetControlPoint(std::vector<Mathematics::Vector3>& controlPoints);

	Mathematics::Vector3 GetWorldPosition();

	void SetRockOn(bool flag);

	bool GetRockOn();

	Object3d& GetTransform();

	virtual void OnCollision();

	bool IsDead() const;//�f�X�t���O�Q�b�^�[

	Enemy() = default;
	~Enemy() = default;

private:
	//�ڋ߃t�F�[�Y
	void ApproachMove();

	//����t�F�[�Y
	void AroundMove();

	void Attack();

	bool AttackFlag();

	void HitUpdate();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Enemy& operator=(const Enemy&) = delete;
	Enemy(const Enemy&) = delete;
};


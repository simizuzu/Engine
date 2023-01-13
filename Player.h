#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Camera.h"
#include "Input.h"
#include "CollisionPrimitive.h"
#include "AudioManager.h"

class Player
{
	// �R���X�g���N�^�E�f�X�g���N�^
	Player();
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Object3d* trans);

	/// <summary>
	/// �Q�[�����̖��t���[������
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���ȊO�̖��t���[������
	/// </summary>
	void titleUpdate();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	Object3d& GetWorldTransform();

	AABB& GetCollider();

	void OnCollision();

	bool GetCrashFlag();

	void SetTransform(Mathematics::Vector3 position);

	void EndGameReset();

	void JumpReset();

private:
	void Move();
	void Rotate();
	void Complement(float& x1, float x2, float flame);
	void Jump();
	void Squat();

	uint8_t jumpFlag = 0u;
	
	float gravitySpeed = 0.5f;
	float defGravitySpeed = gravitySpeed;

	bool crashFlag = false;

	uint32_t crashTime = 70;
	AABB collider_;

	//��]�^�����~�߂�
	bool rollStopFlag = false;

	//���Ⴊ�݃t���O
	bool squatFlag = false;

	Mathematics::Vector3 oldRot;
	uint32_t squatTime = 60 * 2;
	float oldRotY = 0.0f;

	//���f��
	std::shared_ptr<Model> model_;
	// ���[���h�g�����X�t�H�[��
	std::shared_ptr<Object3d> worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Player& operator=(const Player&) = delete;
	Player(const Player&) = delete;

	//�T�E���h
	uint32_t confusionHandle = 0;
};


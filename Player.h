#pragma once
#include <memory>
#include <list>

#include "Model.h"
#include "Input.h"
#include "Object3d.h"
#include "Camera.h"


class Player
{
public:
	Player() = default;
	~Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	/// <summary>
	/// �v���C���[�̋���
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// �e�̋���
	/// </summary>
	void BulletShot();

private:
	// �v���C���[�̍��W
	Mathematics::Vector3 playerPos;
	// �e�̍��W
	Mathematics::Vector3 bulletPos;

	// �v���C���[�̃��f��
	Model* playerModel_ = nullptr;
	Model* bulletModel_ = nullptr;
	
	Object3d* playerObject_ = nullptr;
	Object3d* bulletObject_ = nullptr;

	// ����
	Input* input_ = nullptr;
};


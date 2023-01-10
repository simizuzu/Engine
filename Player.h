#pragma once
#include <memory>
#include "Model.h"
#include "Input.h"
#include "Object3d.h"
#include "Camera.h"

class Player
{
public:
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

	void BulletShot();

private:
	// �v���C���[�̍��W
	Mathematics::Vector3 playerPos;
	// �v���C���[�̃��f��
	Model* playerModel_ = nullptr;
	Model* bulletModel_ = nullptr;
	// ����
	Input* input_ = nullptr;
	
	Object3d* playerObject_ = nullptr;
};


#pragma once
#include <memory>

#include "Input.h"
#include "Object3d.h"
#include "Camera.h"

class Stage
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	Stage() = default;
	~Stage() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="camera">�J����</param>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// ���[���h�g�����X�t�H�[��
	std::shared_ptr<Object3d> WorldTransform_;
	std::shared_ptr<Model> model_;
	
	Mathematics::Vector3 vector_ = {};

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Stage& operator=(const Stage&) = delete;
	Stage(const Stage&) = delete;
};


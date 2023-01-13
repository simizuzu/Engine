#pragma once

#include "Input.h"
#include "Transform.h"
#include "objModel.h"

class door
{
public:

	door();

	~door();

	// <summary>
	/// ������
	/// </summary>
	void Initialize(EngineMathF::Vector3 trans, EngineMathF::Vector3 Rot);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(EngineMathF::Vector3 vector);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	bool GetMashFlag();

	void Reset(EngineMathF::Vector3 trans);

	UINT GetMashNum();

private:

	//�A�ŏ���
	void Mash(EngineMathF::Vector3 vector);

	bool mashFlag_ = false;
	char PADING[3]{};
	UINT mashNum_ = 0;

	Transform door1worldTransform_;
	Transform door2worldTransform_;
	Transform door3worldTransform_;

	std::unique_ptr<objModel> door1model_;
	std::unique_ptr<objModel> door2model_;
	std::unique_ptr<objModel> door3model_;

	Input* input_ = nullptr;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	door& operator=(const door&) = delete;
	door(const door&) = delete;
};


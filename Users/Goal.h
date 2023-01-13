#pragma once
#include "Transform.h"
#include "Camera.h"
#include "objModel.h"
#include "EngineMathUtility.h"
#include <memory>

class Goal
{
public:

	Goal() = default;
	~Goal() = default;

	// <summary>
	/// ������
	/// </summary>
	void Initialize();

	// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

private:
	std::unique_ptr<objModel> model_;
	std::unique_ptr<Transform> worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Goal& operator=(const Goal&) = delete;
	Goal(const Goal&) = delete;
};
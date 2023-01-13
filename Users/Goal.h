#pragma once
#include "lib/engine/3D/Model/Object3d.h"
#include "lib/engine/Camera/Camera.h"
#include "lib/engine/3D/Model/Model.h"

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
	std::unique_ptr<Model> model_;
	std::unique_ptr<Object3d> worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Goal& operator=(const Goal&) = delete;
	Goal(const Goal&) = delete;
};
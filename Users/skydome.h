#pragma once
#include <memory>

#include "lib/engine/3D/Model/Model.h"
#include "lib/engine/3D/Model/Object3d.h"

class skydome
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	skydome() = default;
	~skydome() = default;

	void Initialize();

	void Update(Camera* camera);

	void Draw();

private:
	// ���[���h�g�����X�t�H�[��
	std::shared_ptr<Object3d> transform_;
	// ���f��
	std::shared_ptr<Model> model_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	skydome& operator=(const skydome&) = delete;
	skydome(const skydome&) = delete;
};


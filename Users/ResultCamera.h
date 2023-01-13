#pragma once

#include "Camera.h"
#include "Object3d.h"

class ResultCamera
{
public:

	ResultCamera();
	~ResultCamera();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Object3d* worldTransform);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	Camera* GetViewProjection();

	Object3d* GetWorldTransformPtr();

	void addRot(Mathematics::Vector3 rot);
	void addTranslation(Mathematics::Vector3 translation);

	void setTranslation(Mathematics::Vector3 translation);

private:

	Camera* viewProjection_ = nullptr;

	std::unique_ptr<Object3d>worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ResultCamera& operator=(const ResultCamera&) = delete;
	ResultCamera(const ResultCamera&) = delete;
};

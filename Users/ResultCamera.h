#pragma once

#include"Camera.h"
#include"Transform.h"

class ResultCamera
{
public:

	ResultCamera();
	~ResultCamera();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Transform* worldTransform);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	Camera* GetViewProjection();

	Transform* GetWorldTransformPtr();

	void addRot(EngineMathF::Vector3 rot);
	void addTranslation(EngineMathF::Vector3 translation);

	void setTranslation(EngineMathF::Vector3 translation);

private:

	std::unique_ptr<Camera> viewProjection_;

	Transform worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ResultCamera& operator=(const ResultCamera&) = delete;
	ResultCamera(const ResultCamera&) = delete;
};

#pragma once
#include"Model.h"
#include"Object3d.h"
#include"Camera.h"
#include"CollisionPrimitive.h"

class Object
{
public:

	Object() = default;
	~Object() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Mathematics::Vector3& pos, const Mathematics::Vector3& rot, float radius, Model* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	//�R���C�_�[����
	Sphere& GetCollider();

	//�����������̊֐�
	void OnCollision();

	bool GetIsDeath();

private:
	bool IsDeath;
	char PADING[3]{};
	Sphere collider_;
	char PADING2[4]{};
	Model* model_;
	std::unique_ptr<Object3d> worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Object& operator=(const Object&) = delete;
	Object(const Object&) = delete;
};
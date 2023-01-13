#pragma once
#include"objModel.h"
#include"Transform.h"
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
	void Initialize(const EngineMathF::Vector3& pos, const EngineMathF::Vector3& rot, float radius, objModel* model);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	//�R���C�_�[����
	SPHERE& GetCollider();

	//�����������̊֐�
	void OnCollision();


	bool GetIsDeath();

private:
	bool IsDeath;
	char PADING[3]{};
	SPHERE collider_;
	char PADING2[4]{};
	objModel* model_;
	std::unique_ptr<Transform> worldTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Object& operator=(const Object&) = delete;
	Object(const Object&) = delete;
};
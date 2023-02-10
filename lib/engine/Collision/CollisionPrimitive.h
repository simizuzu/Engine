#pragma once
#include <vector>
#include <array>
#include <string>
#include "Vector3.h"
#include "Vector4.h"
#include "Object3d.h"

/// <summary>
/// �Փ˔�����N���X
/// </summary>
class BaseCollision
{
protected:

	uint32_t collisionAttribute_ = 0xffffffff;
	// �Փ˃}�X�N(����)
	uint32_t collisionMask_ = 0xffffffff;

	// ���O(����)
	std::string collsionName_;
	// ���O(����)
	char opponentCollsionName_[256];

	BaseCollision() = default;
	virtual ~BaseCollision() = default;

public:
	// �Փˎ��ɌĂ΂��֐�
	virtual void OnCollision() = 0;
	// �Փˑ���(����)���擾
	const uint32_t GetCollisionAttribute();
	// �Փˑ���(����)���擾
	void SetCollisionAttribute(uint32_t collisionAttribute);
	// �Փˑ���(����)���擾
	const uint32_t GetCollisionMask();
	// �Փˑ���(����)��ݒ�
	void SetCollisionMask(uint32_t collisionMask);

	// ���O(����)
	void SetCollsionName(std::string name);
	std::string GetCollsionName();

	// ���O(����:Opponent)
	void SetOppCollsionName(std::string name);
	std::string GetOppCollsionName();
};

struct AABB
{
	// ���S���W
	Mathematics::Vector3 center;
	// �T�C�Y
	Mathematics::Vector3 size;
};

struct Sphere
{
	// ���S���W
	Mathematics::Vector4 center;
	// ���a
	float radius;
};

struct Plane
{
	Mathematics::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
	float distance = 0.0f;
};

class BoundingBox : public BaseCollision
{
protected:
	// �ʒu
	Mathematics::Vector3 center = {};
	// �����x�N�g��
	Mathematics::Vector3 directionVec[3];
	// �e�������̒���
	float length[3]{};

public:
	// �w�莲�ԍ��̕����x�N�g�����擾
	const Mathematics::Vector3 GetDirectVec(uint16_t element);
	// �w�莲�����̒������擾
	const float GetLength(uint16_t element);
	// ���S����̈ʒu���擾
	const Mathematics::Vector3 GetCenter();
	// �Փˎ��ɌĂ΂��֐�
	virtual void OnCollision() {};

public:
	/// <summary>
	/// AABB��AABB�̓����蔻��
	/// </summary>
	/// <param name="aabb1">1�ڂ�AABB</param>
	/// <param name="aabb2">2�ڂ�AABB</param>
	/// <returns>true</returns>
	bool CheckAABBToAABB(AABB& aabb1, AABB& aabb2);

	/// <summary>
	/// AABB�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="aabb1">1�ڂ�AABB</param>
	/// <param name="aabb2">��</param>
	/// <returns>false</returns>
	bool CheckAABBToSphere(AABB& aabb,Sphere& sphere);

public:
	/// <summary>
	/// OBB���쐬
	/// </summary>
	/// <param name="vertex">���_</param>
	/// <param name="transform">���[���h�g�����X�t�H�[��</param>
	void CreateOBB(std::vector<VertexPosNormalUv> vertex, Object3d& transform);

	/// <summary>
	/// OBB�̍X�V
	/// </summary>
	/// <param name="transform">���[���h�g�����X�t�H�[��</param>
	void UpdateOBB(Object3d& transform);
};
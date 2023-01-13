#pragma once
#include"Object.h"
#include"player.h"
#include "CollisionPrimitive.h"

class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Player* player);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);
	
	void Reset();
private:
	std::list<std::unique_ptr<Object>>objects_;
	std::unique_ptr<Model> objectModel_;
	std::unique_ptr<Object3d> cubeObject_;

	std::unique_ptr<BoundingBox> aabbToSphere_;

	Player* player_ = nullptr;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&) = delete;
};


#pragma once
#include"Object.h"
#include"EngineMathUtility.h"
#include"player.h"


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
	
	void  Reset();
private:

	std::list<std::unique_ptr<Object>>objects_;
	std::unique_ptr<objModel> objectModel_;
	Player* player_ = nullptr;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ObjectManager& operator=(const ObjectManager&) = delete;
	ObjectManager(const ObjectManager&) = delete;
};


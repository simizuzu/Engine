#pragma once
#include "door.h"
#include "Object3d.h"
#include"DirectX12Math.h"
#include"Model.h"
#include"Sprite.h"

class DoorManager
{
public:

	DoorManager() = default;
	~DoorManager() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Mathematics::Vector3 vector);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(int frequencyInvocationDoor);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

	/// <summary>
/// �X�v���C�g�p�`��
/// </summary>
	void SpriteDraw();

	void  Reset();

	bool GetMashFlag(int frequencyInvocationDoor);

private:
	std::unique_ptr<door> door_[4]={};
	
	Mathematics::Vector3 vector_;

	Mathematics::Vector3 moveVector_;

	TextureData textureHandle_;
	std::unique_ptr<Object3d> transform_;
	std::unique_ptr<Sprite> sprite_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	DoorManager& operator=(const DoorManager&) = delete;
	DoorManager(const DoorManager&) = delete;

};


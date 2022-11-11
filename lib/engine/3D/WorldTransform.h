#pragma once

#include <cassert>
#include "DirectXCommon.h"
#include "Vector3.h"
#include "Matrix4.h"

struct ConstBufferDataWorldTransform
{
	Mathematics::Matrix4 matWorld;
};

class WorldTransform
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�̐���
	/// </summary>
	void CreateConstBuff();

	/// <summary>
	/// �}�b�s���O����
	/// </summary>
	void Map();

	/// <summary>
	/// �s���]������
	/// </summary>
	void TransferMatrix();

private:
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataWorldTransform* constMap_ = nullptr;
	// ���[�J���X�P�[��
	Mathematics::Vector3 scale_ = { 1, 1, 1 };
	// X,Y,Z�����̃��[�J����]�p
	Mathematics::Vector3 rotation_ = { 0, 0, 0 };
	// ���[�J�����W
	Mathematics::Vector3 translation_ = { 0, 0, 0 };
	// ���[�J�� �� ���[���h�ϊ��s��
	Mathematics::Matrix4 matWorld_;
	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
	const WorldTransform* parent_ = nullptr;

	// �N���X�Ăяo��
	DirectXCommon* dxCommon_ = nullptr;
};
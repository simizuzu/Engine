#pragma once
#include "DirectXCommon.h"

#include "Vector3.h"
#include "Vector4.h"
#include "DirectX12Math.h"

/// <summary>
/// ���C�g
/// </summary>
class Light
{
public:
	struct ConstBufferData
	{
		Mathematics::Vector4 lightVec;		//���C�g�ւ̕�����\���x�N�g��
		Mathematics::Vector3 lightColor;	//���C�g�̐F
	};

public:
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialise(DirectXCommon* device);

	/// <summary>
	/// �C���X�^���X����
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Light* Create();

	static DirectXCommon* device_;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList,UINT rootPramIndex);

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightdir">���C�g����</param>
	void SetLightDir(const Mathematics::Vector4& lightdir);

	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	/// <param name="lightColor">���C�g�F</param>
	void SetLightColor(const Mathematics::Vector3& lightColor);

private:
	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

private: //�����o�ϐ�
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//���C�g���������i�P�ʃx�N�g���j
	Mathematics::Vector4 lightdir = {1,0,0,0};
	//���C�g�F
	Mathematics::Vector3 lightColor = { 1.0f,1.0f,1.0f };
	//�_�[�e�B�t���O
	bool dirty = false;
};


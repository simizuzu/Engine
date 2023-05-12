#pragma once
#include "DirectXCommon.h"

#include "Matrix4.h"
#include "Vector3.h"
#include "DirectX12Math.h"

/// <summary>
/// ���C�g
/// </summary>
class Light
{
public:
	struct ConstBufferData
	{
		Mathematics::Matrix4 lightVec;		//���C�g�ւ̕�����\���x�N�g��
		Mathematics::Vector3 lightColor;	//���C�g�̐F
	};

public: //�ÓI�����o�֐�
	static void StaticInitialize(DirectXCommon* device);

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static DirectXCommon* device_;

public:
	void Initialize();

private: //�����o�ϐ�
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//���C�g���������i�P�ʃx�N�g���j
	Mathematics::Matrix4 lightdir = MyMathUtility::MakeIdentity();
	//���C�g�F
	Mathematics::Vector3 lightColor = { 1.0f,1.0f,1.0f };
	//�_�[�e�B�t���O
	bool dirty = false;
};


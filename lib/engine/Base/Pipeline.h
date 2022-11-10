#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Sprite.h"
#include "DirectXCommon.h"

class Pipeline
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(�X�v���C�g)
	/// </summary>
	void CreateSpritePipeline();

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(���f��)
	/// </summary>
	void CreateModelPipeline();

private: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> vsBlob;
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;
	// �G���[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	// �p�C�v���C���X�e�[�g
	ComPtr<ID3D12PipelineState> pipelineState;

	// �N���X�Ăяo��
	Sprite* sprite_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
};


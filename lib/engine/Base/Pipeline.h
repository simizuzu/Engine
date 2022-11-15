#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Sprite.h"
#include "DirectXCommon.h"

class Pipeline
{
public:
	enum class BlendMode
	{
		None,	// �u�����h����
		Alpha,	// �A���t�@
		Add,	// ���Z
		Sub,	// ���Z
		Mul,	// ��Z
		Inv,	// �F���]

		CountOfBlendMode, // �ő�u�����h���[�h��
	};

public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(�X�v���C�g)
	/// </summary>
	void CreateSpritePipeline();

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(���f��)
	/// </summary>
	//void CreateModelPipeline();

public:
	void SetBlendMode(int blendMode) { };

private: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g
	ComPtr<ID3D12PipelineState> pipelineState;
	// �u�����h�f�X�N
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc;

	// �N���X�Ăяo��
	Sprite* sprite_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
};


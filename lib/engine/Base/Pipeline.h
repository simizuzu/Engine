#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <array>
#include "DirectXCommon.h"

enum class BlendMode
{
	None,	// �u�����h����
	Alpha,	// �A���t�@
	Add,	// ���Z
	Sub,	// ���Z
	Mul,	// ��Z
	Inv,	// �F���]
};

struct RootsigSetPip
{
	// ���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

class Pipeline
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(�X�v���C�g)
	/// </summary>
	static void CreateSpritePipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend,ID3D12Device* device, std::array<RootsigSetPip,6>&pipeline);

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(3D�I�u�W�F�N�g)
	/// </summary>
	static void CreateObjPipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend, ID3D12Device* device, RootsigSetPip& pipeline);

private: // �����o�ϐ�

	// �N���X�Ăяo��
	DirectXCommon* dxCommon_ = nullptr;
};

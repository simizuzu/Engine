#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <array>
#include "DirectXCommon.h"
#include "EngineUtility.h"
#include "AvoidWarning.h"

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

	/// <summary>
	/// �p�C�v���C���Ăяo���p�֐�(�p�[�e�B�N��)
	/// </summary>
	static void CreatePaticlePipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, ID3DBlob* gsBlob, ID3D12Device* device, RootsigSetPip& pipeline);

	static void CreatePostEffectPipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, ID3D12Device* device, RootsigSetPip& pipeline);

private: // �����o�ϐ�

	// �N���X�Ăяo��
	DirectXCommon* dxCommon_ = nullptr;
};


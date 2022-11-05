#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <wrl.h>
#include <DirectXTex.h>

/// <summary>
/// �e�N�X�`���}�l�[�W��
/// </summary>
class TextureManager
{
public: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �萔
	static const int MaxSRVCount = 512; // �e�N�X�`���̍ő喇��

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="directXCommon"></param>
	void Initialize(DirectXCommon* directXCommon);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�e�N�X�`���t�@�C����</param>
	void LoadTexture(UINT texNumber, const wchar_t* filename);

	/// <summary>
	/// �e�N�X�`���o�b�t�@�擾
	/// </summary>
	/// <param name="texNumber"></param>
	/// <returns>�e�N�X�`���o�b�t�@</returns>
	ID3D12Resource* GetTexBuff(UINT texNumber);

	/// <summary>
	/// �f�X�N���v�^�q�[�v���Z�b�g�i�O���t�B�b�N�X�R�}���h�j
	/// </summary>
	/// <param name="commandList">�R�}���h���X�g</param>
	void SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// SRV���Z�b�g�i�O���t�B�b�N�X�R�}���h�j
	/// </summary>
	/// <param name="commandList">�R�}���h���X�g</param>
	/// <param name="rootPrameterIndex">���[�g�p�����[�^�̔ԍ�</param>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	void SetGraphicsRootDesCriptorTable(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber);

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private: // �����o�ϐ�
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	ComPtr<ID3D12Resource> texBuff[MaxSRVCount];

	//ComPtr<ID3D12Resource> texBuff;

	// GPU�f�X�N���v�^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// �f�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;

	D3D12_HEAP_PROPERTIES texHeapProp;

	DirectXCommon* directXCommon_ = nullptr;
};


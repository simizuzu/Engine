#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <wrl.h>
#include <DirectXTex.h>
#include <array>

struct TextureData
{
	// �e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// �f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//GPU�f�X�N���v�^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// �f�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange;

	// ����
	size_t width = 0;
	// �c��
	size_t height = 0;
};

/// <summary>
/// �e�N�X�`���}�l�[�W��
/// </summary>
class TextureManager
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �萔
	static const size_t MaxSRVCount = 1024; // �e�N�X�`���̍ő喇��

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="directXCommon"></param>
	void Initialize(DirectXCommon* directXCommon);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="filename">�e�N�X�`���t�@�C����</param>
	void LoadTexture(const std::string& fileName);

	/// <summary>
	/// �f�X�N���v�^�q�[�v���Z�b�g�i�O���t�B�b�N�X�R�}���h�j
	/// </summary>
	/// <param name="commandList">�R�}���h���X�g</param>
	void SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// �V�F�[�_�[���\�[�X�r���[���Z�b�g
	/// </summary>
	/// <param name="commandList">�R�}���h���X�g</param>
	/// <param name="rootPrameterIndex">���[�g�p�����[�^</param>
	/// <param name="texNumber">�e�N�X�`���ԍ�</param>
	void SetShaderResourceView(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber);

	// �C���X�^���X
	static TextureManager* GetInstance();

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private: // �����o�ϐ�
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	D3D12_HEAP_PROPERTIES textureHeapProp;

	// �e�N�X�`����
	UINT texCount;

	DirectXCommon* directXCommon_ = nullptr;

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&) = delete;
};


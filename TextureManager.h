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
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle{};
	// �f�X�N���v�^�����W
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

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
	static const size_t MaxSRVCount = 256; // �e�N�X�`���̍ő喇��

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
	TextureData LoadTexture(const std::string& fileName);

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <returns>�e�N�X�`���n���h��</returns>
	static TextureData Load(const std::string& fileName);

	/// <summary>
	/// �e�N�X�`���o�b�t�@�̐���
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg);

	/// <summary>
	/// �V�F�[�_���\�[�X�r���[�̐���
	/// </summary>
	/// <param name="texbuff">�e�N�X�`���o�b�t�@</param>
	/// <param name="metadata"></param>
	D3D12_GPU_DESCRIPTOR_HANDLE CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata);

	/// <summary>
	/// �������
	/// </summary>
	void Delete();

	// �C���X�^���X
	static TextureManager* GetInstance();

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private: // �����o�ϐ�
	ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	// �e�N�X�`���o�b�t�@
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, MaxSRVCount> texBuff_;
	// �e�N�X�`����
	UINT texCount;
	// �f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string DefaultTextureDirectoryPath;

	DirectXCommon* dxCommon_ = nullptr;
	static TextureManager* textureManager_;

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&) = delete;
};
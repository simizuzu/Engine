#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <vector>
#include <wrl.h>
#include <DirectXTex.h>
#include <array>
#include "EngineUtility.h"

/// <summary>
/// �e�N�X�`���}�l�[�W��
/// </summary>
class TextureManager
{
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
	/// �������
	/// </summary>
	void Delete();

	// �C���X�^���X
	static TextureManager* GetInstance();

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private:
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

	[[nodiscard]]
	ID3D12Resource* UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;
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
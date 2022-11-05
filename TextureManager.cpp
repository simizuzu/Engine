#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

void TextureManager::Initialize(DirectXCommon* directXCommon)
{
	HRESULT result;

	// �����o�ϐ��ɋL�^
	directXCommon_ = directXCommon;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = MaxSRVCount;
	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = directXCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));
}

void TextureManager::LoadTexture(UINT texNumber, const wchar_t* filename)
{
	HRESULT result;

	// WIC�e�N�X�`���̃��[�h
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// �~�b�v�}�b�v����
	result = DirectX::GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// �ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = DirectX::MakeSRGB(metadata.format);

	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC texResourceDesc{};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texResourceDesc.Format = metadata.format;
	texResourceDesc.Width = metadata.width;
	texResourceDesc.Height = (UINT)metadata.height;
	texResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	texResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	texResourceDesc.SampleDesc.Count = 1;

	// �e�N�X�`���p�̃o�b�t�@�̐���
	result = directXCommon_->GetDevice()->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&texResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff[texNumber]));

	// �S�~�b�v�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// �~�b�v�}�b�v���x���𐧒肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff[texNumber]->WriteToSubresource(
			(UINT)i,
			nullptr,
			img->pixels,
			(UINT)img->rowPitch,
			(UINT)img->slicePitch
		);
		assert(SUCCEEDED(result));
	}
	
	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	// SRV�q�[�v�̐擪�n���h�����擾
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	// �f�X�N���v�^1���A�h���X��i�߂�
	srvHandle.ptr += directXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// �V�F�[�_�[���\�[�X�r���[�ݒ�
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	// �q�[�v��2�ԖڂɃV�F�[�_�[���\�[�X�r���[�쐬
	directXCommon_->GetDevice()->CreateShaderResourceView(
		texBuff[texNumber].Get(),	// �r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc,		// �e�N�X�`���ݒ���
		srvHandle
	);
}

ID3D12Resource* TextureManager::GetTexBuff(UINT texNumber)
{
	// �w�肵�������ȉ��œ����悤�ɐݒ肷��
	assert(texNumber < MaxSRVCount);

	return texBuff[texNumber].Get();
}

void TextureManager::SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList)
{
	// �f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void TextureManager::SetGraphicsRootDesCriptorTable(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber)
{
	// �f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// �V�F�[�_���\�[�X�r���[���Z�b�g
	commandList->SetGraphicsRootDescriptorTable(rootPrameterIndex, srvGpuHandle);
}

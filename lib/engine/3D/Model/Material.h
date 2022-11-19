#pragma once

#include <vector>
#include <d3d12.h>
#include <wrl.h>

#include "TextureManager.h"

struct ShaderFile
{
	//�V�F�[�_�[�t�@�C���p�X
	std::wstring pFileName;
	//�G���g���[�|�C���g
	std::string pEntrypoint;
	//�o�[�W����
	std::string pTarget;
};

class Material
{
public:
	//�e�N�X�`���f�[�^
	TextureData textureData;

	//���_�V�F�[�_�[
	ShaderFile vsFiledata{ {},{"main"},{"vs_5_0"} };
	//�s�N�Z���V�F�[�_�[
	ShaderFile psFiledata{ {},{"main"},{"ps_5_0"} };

	//���_���C�A�E�g
	std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayouts;

	//���[�g�p�����[�^
	std::vector<D3D12_ROOT_PARAMETER> rootParams;

	//�u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};

	//�p�C�v���C���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;

	//���[�g�V�O�l�`��
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;

	bool depthFlag = true;
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	//void copy(const Material* material);
	//void copy(const Material& material);
	Material* copy();

	Material() = default;
	~Material() = default;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Material(const Material&) = delete;
};
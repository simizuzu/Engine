#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <vector>
#include <string>
#include <wrl.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include "TextureManager.h"
#include "DirectXCommon.h"

struct VertexPosNormalUv
{
	Mathematics::Vector3 pos;		// xyz���W
	Mathematics::Vector3 normal;	// �@���x�N�g��
	Mathematics::Vector2 uv;		// uv���W
};

struct Material
{
	std::string name;				// �}�e���A����
	Mathematics::Vector3 ambient;	// �A���r�G���g�e���x
	Mathematics::Vector3 diffuse;	// �f�B�t���[�Y�e���x
	Mathematics::Vector3 specular;	// �X�y�L�����[�e���x
	float alpha;					// �A���t�@
	std::string textureFilename;	// �e�N�X�`���t�@�C����

	// �R���X�g���N�^
	Material() {
		ambient = { 0.3f,0.3f,0.3f };
		diffuse = { 0.0f,0.0f,0.0f };
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};

/// <summary>
/// 3D���f��
/// </summary>
class Model
{
public:
	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		Mathematics::Vector3 ambient;	// �A���r�G���g�W��
		float pad1;						// �p�f�B���O
		Mathematics::Vector3 diffuse;	// �f�B�t���[�Y�W��
		float pad2;						// �p�f�B���O
		Mathematics::Vector3 specular;	// �X�y�L�����[�W��
		float alpha;					// �A���t�@
	};

public:
	/// <summary>
	/// OBJ�t�@�C������3D���f����ǂݍ���
	/// </summary>
	/// <returns>���f��</returns>
	static Model* LoadFromObj(const std::string& modelname);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	/// <param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	static void SetDevice(ID3D12Device* device) { Model::device = device; };

private: // �ÓI�����o�ϐ�
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// �e�N�X�`���o�b�t�@
	static Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(GPU)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	static std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	static std::vector<unsigned short> indices;
	// �}�e���A��
	static Material material;

private: // �����o�ϐ�
	// �萔�o�b�t�@�i�}�e���A���j
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �e�N�X�`���f�[�^
	TextureData textureData;
private:
	/// <summary>
	/// OBJ�t�@�C������3D���f����ǂݍ���
	/// </summary>
	void LoadFromOBJInternal(const std::string& modelname);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �e��o�b�t�@����
	/// </summary>
	void CreateBuffers();

	/// <summary>
	/// ���_�f�[�^�S�̂̃T�C�Y
	/// </summary>
	void CreateVBSize();

	/// <summary>
	/// �C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	/// </summary>
	void CreateIBSize();
};


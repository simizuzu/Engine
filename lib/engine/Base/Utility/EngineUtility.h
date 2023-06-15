#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

// �萔�o�b�t�@�p�f�[�^�\����
struct ConstBufferDataB0
{
	//Mathematics::Matrix4 mat;	// 3D�ϊ��s��
	MyMath::Matrix4 viewproj;
	MyMath::Matrix4 world;
	MyMath::Vector3 cameraPos;
};

struct ConstBufferDataViewProjection
{
	// ���[���h�s��
	MyMath::Matrix4 world;
	// ���[���h���W
	MyMath::Matrix4 matWorld;

	// ���[���h �� �r���[�ϊ��s��
	MyMath::Matrix4 view;
	// �r���[ �� �v���W�F�N�V�����ϊ��s��
	MyMath::Matrix4 projection;
	// �J�������W�i���[���h���W�j
	MyMath::Vector3 cameraPos;
};

struct ViewProjection
{
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataViewProjection* constBuffMap = nullptr;
};

struct VertexPosNormalUv
{
	MyMath::Vector3 pos;		// xyz���W
	MyMath::Vector3 normal;	// �@���x�N�g��
	MyMath::Vector2 uv;		// uv���W
};

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

//�r���{�[�h�萔�o�b�t�@�p�f�[�^�\����
struct ParticleConstBuffData
{
	MyMath::Matrix4 mat;
	MyMath::Matrix4 matBillboard;
};

//�J�����\����
struct WorldvViewProCamera
{
	//���[���h�s��
	MyMath::Matrix4 world;
	//���[���h���W
	MyMath::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	MyMath::Vector3 cameraPos;
};

struct VertexPos
{
	MyMath::Vector3 pos;	//xyz���W
	float scale;			//�X�P�[��
	MyMath::Vector4 color;	//�F
};

// �p�[�e�B�N��1��
struct Particle
{
	// ���W
	MyMath::Vector3 position = {};
	// ���x
	MyMath::Vector3 velocity = {};
	// �����x
	MyMath::Vector3 accel = {};
	// ���݃t���[��
	int frame = 0;
	// �I���t���[��
	int num_frame = 0;
	// �X�P�[��
	float scale = 1.0f;
	// �����l
	float s_scale = 1.0f;
	// �ŏI�l
	float e_scale = 0.0f;
	// �F
	MyMath::Vector4 color = { 1,1,1,1 };
	MyMath::Vector4 s_color = { 1,0,0,1 };
	MyMath::Vector4 e_color = { 1,1,1,1 };
};
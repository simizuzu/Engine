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
	Mathematics::Matrix4 mat;	// 3D�ϊ��s��
};

struct ConstBufferDataViewProjection
{
	// ���[���h�s��
	Mathematics::Matrix4 world;
	// ���[���h���W
	Mathematics::Matrix4 matWorld;

	// ���[���h �� �r���[�ϊ��s��
	Mathematics::Matrix4 view;
	// �r���[ �� �v���W�F�N�V�����ϊ��s��
	Mathematics::Matrix4 projection;
	// �J�������W�i���[���h���W�j
	Mathematics::Vector3 cameraPos;
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
	Mathematics::Vector3 pos;		// xyz���W
	Mathematics::Vector3 normal;	// �@���x�N�g��
	Mathematics::Vector2 uv;		// uv���W
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
	Mathematics::Matrix4 mat;
	Mathematics::Matrix4 matBillboard;
};

//�J�����\����
struct WorldvViewProCamera
{
	//���[���h�s��
	Mathematics::Matrix4 world;
	//���[���h���W
	Mathematics::Matrix4 matWorld;
	//�J�������W(���[���h���W)
	Mathematics::Vector3 cameraPos;
};

struct VertexPos
{
	Mathematics::Vector3 pos;	//xyz���W
	float scale;			//�X�P�[��
	Mathematics::Vector4 color;	//�F
};

// �p�[�e�B�N��1��
struct Particle
{
	// ���W
	Mathematics::Vector3 position = {};
	// ���x
	Mathematics::Vector3 velocity = {};
	// �����x
	Mathematics::Vector3 accel = {};
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
	Mathematics::Vector4 color = { 1,1,1,1 };
	Mathematics::Vector4 s_color = { 1,0,0,1 };
	Mathematics::Vector4 e_color = { 1,1,1,1 };
};
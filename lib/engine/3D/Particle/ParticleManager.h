#pragma once
#include "AvoidWarning.h"
#include "Shader.h"
#include "Pipeline.h"
#include "DirectXCommon.h"
#include "WorldTransform.h"
#include "Vector4.h"


class ParticleManager
{
public:
	static void StaticInitialize(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

private:
	void InitializeDescriptorHeap();
	static void CreateCraphicsPipeline();

public:

	void Initialize();
	
	void Draw(WorldTransform* transform);

	void Update();

	void LoadTexture(const wchar_t* texturename);
	void CreateModel();

	void Add(int life, MyMath::Vector3 position, MyMath::Vector3 velocity, MyMath::Vector3 accel, float start_scale, float end_scale, MyMath::Vector4 s_color, MyMath::Vector4 e_color);

	void RandParticle();

private:
	static const int vertexCount = 1024;	// ���_��

private:
	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// �R�}���h���X�g
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	// �p�C�v���C���X�e�[�g
	static RootsigSetPip pip;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	Microsoft::WRL::ComPtr<ID3D12Resource> texbuff;
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	UINT descriptorHandleIncrementSize;
	// ���_�f�[�^�z��
	VertexPos vertices[vertexCount];
	D3D12_VERTEX_BUFFER_VIEW vbView;

	MyMath::Matrix4 matView;
	MyMath::Matrix4 matProjection;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	std::forward_list<Particle> particles;
};


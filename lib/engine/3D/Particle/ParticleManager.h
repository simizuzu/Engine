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
	static void LoadTexture(const wchar_t* texturename);
private:
	static void InitializeDescriptorHeap();
	static void CreateCraphicsPipeline();

	static void CreateModel();

public:
	void Draw(WorldTransform* transform);

	void Update();

	void Add(int life, Mathematics::Vector3 position, Mathematics::Vector3 velocity, Mathematics::Vector3 accel, float start_scale, float end_scale, Mathematics::Vector4 s_color, Mathematics::Vector4 e_color);

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

	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	static Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	static Microsoft::WRL::ComPtr<ID3D12Resource> texbuff;
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	static UINT descriptorHandleIncrementSize;
	// ���_�f�[�^�z��
	static VertexPos vertices[vertexCount];
	static D3D12_VERTEX_BUFFER_VIEW vbView;

	static Mathematics::Matrix4 matView;
	static Mathematics::Matrix4 matProjection;

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	std::forward_list<Particle> particles;
};


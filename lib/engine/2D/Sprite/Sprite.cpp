#include "Sprite.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device* Sprite::device_ = nullptr;
UINT Sprite::descriptorSize_;
ID3D12GraphicsCommandList* Sprite::commandList_ = nullptr;
ComPtr<ID3D12RootSignature> Sprite::rootSignature_;
std::array<RootsigSetPip, 6> Sprite::pipelineState;
Mathematics::Matrix4 Sprite::matProjection_;
ComPtr<ID3DBlob> Sprite::vsBlob = nullptr;
ComPtr<ID3DBlob> Sprite::psBlob = nullptr;
Shader* Sprite::shader_ = nullptr;
Pipeline* Sprite::pipeline_ = nullptr;

void Sprite::StaticInitialize()
{
	device_ = DirectXCommon::GetInstance()->GetDevice();
	commandList_ = DirectXCommon::GetInstance()->GetCommandList();

	float width = static_cast<float>(WinApp::GetInstance()->window_width);
	float height = static_cast<float>(WinApp::GetInstance()->window_height);

	// �f�X�N���v�^�T�C�Y���擾
	descriptorSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// ���s���e
	XMmatProjection_ = XMMatrixOrthographicOffCenterLH(
		0.0f, winApp_->GetInstance()->window_width,
		winApp_->GetInstance()->window_height, 0.0f,
		0.0f, 1.0f);

	shader_->CreateSpriteShade(vsBlob.Get(), psBlob.Get());

	for (int i = 0; i < pipelineState.size(); i++)
	{
		pipeline_->CreateSpritePipeline(vsBlob.Get(), psBlob.Get(), (BlendMode)i, device_, pipelineState);
	}
}

void Sprite::PreDraw()
{
	assert(Sprite::commandList_ == nullptr);

	// �R�}���h���X�g //

}

void Sprite::PostDraw()
{
}

void Sprite::Initialize()
{
	InitializeVertexBuff();
}

void Sprite::Update()
{

}

void Sprite::Draw()
{
	// ���_�f�[�^
	XMFLOAT3 vertices[] = {
		{-0.5f, -0.5f, 0.0f}, // ����
		{-0.5f, +0.5f, 0.0f}, // ����
		{+0.5f, -0.5f, 0.0f}, // �E��
	};
	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));
}

void Sprite::InitializeVertexBuff()
{
	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};		// �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	HRESULT result = dxCommon_->GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,	// �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	// ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	// ���W���R�s�[
	}
	// �Ȃ��������
	vertBuff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(XMFLOAT3);
}
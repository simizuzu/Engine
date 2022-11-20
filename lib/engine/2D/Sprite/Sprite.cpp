#include "Sprite.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace Mathematics;
using namespace MyMathUtility;

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ComPtr<ID3D12Device> Sprite::device_;
UINT Sprite::descriptorSize_;
ComPtr<ID3D12GraphicsCommandList> Sprite::commandList_;
ComPtr<ID3D12RootSignature> Sprite::rootSignature_;
std::array<RootsigSetPip, 6> Sprite::pipelineState;
Mathematics::Matrix4 Sprite::matProjection_;
Shader* Sprite::shader_ = nullptr;
Pipeline* Sprite::pipeline_ = nullptr;

void Sprite::StaticInitialize()
{
	device_ = DirectXCommon::GetInstance()->GetDevice();
	commandList_ = DirectXCommon::GetInstance()->GetCommandList();
	shader_ = new Shader();
	pipeline_ = new Pipeline();

	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> psBlob;

	float width = static_cast<float>(WinApp::GetInstance()->window_width);
	float height = static_cast<float>(WinApp::GetInstance()->window_height);

	// �f�X�N���v�^�T�C�Y���擾
	descriptorSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// ���s���e
	MyMathUtility::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection_);

	// �V�F�[�_�[�̓ǂݍ���
	shader_->CreateSpriteShade(vsBlob, psBlob);

	for (int i = 0; i < pipelineState.size(); i++)
	{
		pipeline_->CreateSpritePipeline(vsBlob.Get(), psBlob.Get(), (BlendMode)i, device_.Get(), pipelineState);
	}
}

void Sprite::Initialize()
{
	CreateVertexIndexBuff();
	CreateConstBuff();
}

void Sprite::Update(Mathematics::Vector2 pos, Mathematics::Vector2 scale, float rot)
{
	Mathematics::Matrix4 mTrans, mRot, mScale, matWorld;
	mTrans = MakeTranslation({ pos.x,pos.y,0.0f });
	mRot = MakeRotation({ 0.0f,0.0f,rot });
	mScale = MakeScaling({ scale.x,scale.y,1.0f });
	matWorld = mScale * mRot * mTrans;

	*constBuffMap = matWorld * matProjection_;
}

void Sprite::DrawSprite(TextureData& textureData, Mathematics::Vector2 position, Mathematics::Vector2 scale, float rotation,
	Mathematics::Vector2 anchorpoint, bool flipX, bool flipY)
{
	int isFlipX, isFlipY;
	if (flipX == false)isFlipX = 1;
	else isFlipX = -1;
	if (flipY == false)isFlipY = 1;
	else isFlipY = -1;

	float left = ((0.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float right = ((1.0f - anchorpoint.x) * textureData.width) * isFlipX;
	float top = ((0.0f - anchorpoint.y) * textureData.height) * isFlipY;
	float bottom = ((1.0f - anchorpoint.y) * textureData.height) * isFlipY;

	//���_�f�[�^
	PosUvColor vertices[] =
	{
		{{left,top,0.0f},{0.0f,0.0f}},//����C���f�b�N�X0
		{{left,bottom,0.0f},{0.0f,1.0f}},//�����C���f�b�N�X1
		{{right,top,0.0f},{1.0f,0.0f}},//�E��C���f�b�N�X2
		{{right,bottom,0.0f},{1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	//�C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1,0,3,//�O�p�`1��
		2,3,0,//�O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];//�C���f�b�N�X���R�s�[
	}

	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];//�C���f�b�N�X���R�s�[
	}

	Update(position, scale, rotation);

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	SetBlendMode((BlendMode)blendMode);

	DrawCommandList(textureData);

	// �`��R�}���h
	commandList_->DrawIndexedInstanced(_countof(indices), 1, 0, 0, 0);
}

void Sprite::DrawCommandList(TextureData textureData)
{
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	commandList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	commandList_->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	commandList_->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	//SRV�q�[�v�̐ݒ�R�}���h
	commandList_->SetDescriptorHeaps(1, textureData.srvHeap.GetAddressOf());
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w���Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = textureData.srvGpuHandle;
	//SRV�q�[�v�擪�ɂ���SRV�����[�g�p�����[�^�[1�Ԃɐݒ�
	commandList_->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	commandList_->IASetIndexBuffer(&ibView);
}

void Sprite::CreateVertexIndexBuff()
{
	HRESULT result;

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^�T�C�Y����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * 4);

	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//���_�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapProp,//���\�[�X�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//���_�o�b�t�@�r���[�̍쐬
	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(PosUvColor);

	//�C���f�b�N�X�f�[�^�̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * 6);
	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�@
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(indexBuff.ReleaseAndGetAddressOf()));

	//�C���f�b�N�X�o�b�t�@�̃}�b�s���O
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	assert(SUCCEEDED(result));
}

void Sprite::CreateConstBuff()
{
	HRESULT result;

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(Matrix4) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(constBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	//�萔�o�b�t�@�̃}�b�s���O
	result = constBuff->Map(0, nullptr, (void**)&constBuffMap);//�}�b�s���O
	assert(SUCCEEDED(result));
}

void Sprite::SetBlendMode(BlendMode mode)
{
	switch (mode)
	{
	case BlendMode::None:

		commandList_->SetPipelineState(pipelineState[0].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[0].rootSignature.Get());

		break;

	case BlendMode::Alpha:

		commandList_->SetPipelineState(pipelineState[1].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[1].rootSignature.Get());

		break;

	case BlendMode::Add:

		commandList_->SetPipelineState(pipelineState[2].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[2].rootSignature.Get());

		break;

	case BlendMode::Sub:

		commandList_->SetPipelineState(pipelineState[3].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[3].rootSignature.Get());

		break;

	case BlendMode::Mul:

		commandList_->SetPipelineState(pipelineState[4].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[4].rootSignature.Get());

		break;

	case BlendMode::Inv:

		commandList_->SetPipelineState(pipelineState[5].pipelineState.Get());
		commandList_->SetGraphicsRootSignature(pipelineState[5].rootSignature.Get());

		break;
	}
}

void Sprite::Delete()
{
	delete shader_;
	delete pipeline_;
}

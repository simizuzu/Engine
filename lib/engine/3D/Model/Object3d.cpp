#include "Object3d.h"
#include <windows.h>

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> Object3d::device_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Object3d::cmdList_;
Pipeline* Object3d::pipeline = nullptr;

void Object3d::StaticInitialize(ID3D12Device* device, int width, int height)
{
	// nullptr�`�F�b�N
	assert(device);

	Object3d::device_ = device;

	Model::SetDevice(device);
}

void Object3d::CreateGraphicsPipeline()
{

}

Object3d* Object3d::Create()
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object3d* object3d = new Object3d();
	if (object3d == nullptr)
	{
		return nullptr;
	}

	// ������
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	return object3d;
}

bool Object3d::Initialize()
{
	HRESULT result;

	//�萔�o�b�t�@�̐���
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p

	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataB0) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1));
	assert(SUCCEEDED(result));

	return true;
}

void Object3d::Update()
{
}

void Object3d::Draw()
{
}

void Object3d::UpdateViewMatrix()
{
}

#include "Camera.h"
#include "DirectXCommon.h"
#include "WinApp.h"

using namespace MyMathUtility;

ViewProjection viewPro;
ConstBufferDataViewProjection ConstMap;

void Camera::Initialize()
{
	eye_ = { 0,0,-distance };//���_���W
	target_ = { 0,0,0 };//�����_���W
	up_ = { 0,1,0 };//������x�N�g��

	nearZ_ = 0.1f;
	farZ_ = 1000.0f;

	// �A�X�y�N�g����v�Z(��ʉ���/��ʏc��)
	aspect = 
		static_cast<float>(WinApp::GetInstance()->window_width) /
		static_cast<float>(WinApp::GetInstance()->window_height);

	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::CreateConstBuffer()
{
	HRESULT result;

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(viewPro.constBuff_.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void Camera::Map()
{
	HRESULT result;

	//�萔�o�b�t�@�̃}�b�s���O
	result = viewPro.constBuff_->Map(0, nullptr, (void**)&viewPro.constBuffMap);//�}�b�s���O
	assert(SUCCEEDED(result));
}

void Camera::UpdateMatrix()
{
	// �r���[�s��̐���
	matView_ = MakeLookAtLH(eye_, target_, up_);
	// �t�s��
	matViewInverse_ = MakeInverse(matView_);
	// �������e�̐���
	matProjection_ = MakePerspective(fovAngleY, aspect, nearZ_, farZ_);
	// �萔�o�b�t�@�ɓ]��
	TransferMatrix();
}

void Camera::TransferMatrix()
{
	// �萔�o�b�t�@�ɏ�������
	ConstMap.view = matView_;
	ConstMap.projection = matProjection_;
	ConstMap.cameraPos = eye_;
}

const Mathematics::Matrix4& GetMatView()
{
	return matView_;
}
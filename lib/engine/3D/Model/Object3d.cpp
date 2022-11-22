#include "Object3d.h"
#include <windows.h>

#include "DirectX12Math.h"

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> Object3d::device_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Object3d::cmdList_;
Mathematics::Vector3 Object3d::eye = { 0.0f,3.0f,-10.0f };
Mathematics::Vector3 Object3d::target = { 0.0f,0.0f,0.0f };
Mathematics::Vector3 Object3d::up = { 0.0f,1.0f,0.0f };
std::unique_ptr<Pipeline> Object3d::pipeline = std::make_unique<Pipeline>();
RootsigSetPip Object3d::pip;
Camera* Object3d::camera = nullptr;

void Object3d::StaticInitialize(ID3D12Device* device, int width, int height)
{
	// nullptr�`�F�b�N
	assert(device);

	Object3d::device_ = device;

	// �O���t�B�b�N�X�p�C�v���C���̐���
	CreateGraphicsPipeline();

	Model::SetDevice(device);

	InitializeCamera();
}

void Object3d::CreateGraphicsPipeline()
{
	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;	// �s�N�Z���V�F�[�_�I�u�W�F�N�g

	Shader::CreateObjShade(vsBlob, psBlob);

	Pipeline::CreateObjPipeline(vsBlob.Get(), psBlob.Get(), BlendMode::None, device_.Get(),pip);
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

void Object3d::UpdateViewMatrix()
{
	// ���_���W
	Mathematics::Vector3 eyeProjection = eye;
	// �����_���W
	Mathematics::Vector3 targetPosition = target;
	// �����
	Mathematics::Vector3 upVector = up;

	// �J����Z���i���������j
	Mathematics::Vector3 cameraAxisZ;
}

void Object3d::InitializeCamera()
{
	//camera->Initialize();
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

	result = device_->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));
	assert(SUCCEEDED(result));

	return true;
}

void Object3d::Update(Camera* camera)
{
	HRESULT result;
	Mathematics::Matrix4 matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = MyMathUtility::MakeScaling(scale);
	matRot = MyMathUtility::MakeIdentity();
	matRot = MyMathUtility::MakeRotation(rotation);
	matTrans = MyMathUtility::MakeTranslation(position);

	// ���[���h�s��̍���
	matWorld = MyMathUtility::MakeIdentity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;

	// �e�I�u�W�F�N�g�������
	if (parent != nullptr)
	{
		matWorld *= parent->matWorld;
	}

	const Mathematics::Matrix4 matView = camera->GetMatView();
	const Mathematics::Matrix4 matProjection = camera->GetMatProjection();

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	constMap->mat = matWorld* matView * matProjection;
	constBuffB0->Unmap(0, nullptr);
}

void Object3d::Draw()
{
	cmdList_ = DirectXCommon::GetInstance()->GetCommandList();

	// null�`�F�b�N
	assert(device_);
	assert(Object3d::cmdList_);

	// ���f���̊��蓖�Ă��Ȃ���Ε`�悵�Ȃ�
	if (model == nullptr)
	{
		return;
	}

	// �p�C�v���C���X�e�[�g�̐ݒ�
	cmdList_->SetPipelineState(pip.pipelineState.Get());
	// ���[�g�V�O�l�`���̐ݒ�
	cmdList_->SetGraphicsRootSignature(pip.rootSignature.Get());
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList_->SetGraphicsRootConstantBufferView(2, constBuffB0->GetGPUVirtualAddress());

	// ���f���`��
	model->Draw(cmdList_.Get());
}
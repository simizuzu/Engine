#include "Object3d.h"
#include <windows.h>

#include "DirectX12Math.h"

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> Object3d::device_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Object3d::cmdList_;
RootsigSetPip Object3d::pip;
Light* Object3d::light = nullptr;

void Object3d::StaticInitialize(ID3D12Device* device, int width, int height)
{
	// nullptr�`�F�b�N
	assert(device);

	Object3d::device_ = device;

	// �O���t�B�b�N�X�p�C�v���C���̐���
	CreateGraphicsPipeline();

	Model::SetDevice(device);
}

void Object3d::CreateGraphicsPipeline()
{
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob;	// �s�N�Z���V�F�[�_�I�u�W�F�N�g

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
	const Mathematics::Vector3& cameraPos = camera->GetEye();

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
	//constMap->mat = matWorld* matView * matProjection;
	constMap->viewproj = matView * matProjection;
	constMap->world = matWorld;
	constMap->cameraPos = cameraPos;
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

	//���C�g�̕`��
	light->Draw(cmdList_.Get(), 3);
	// ���f���`��
	model->Draw(cmdList_.Get());
}

void Object3d::SetModel(Model* model)
{
	this->model = model;
}

void Object3d::SetLight(Light* light)
{
	Object3d::light = light;
}

void Object3d::SetPosition(Mathematics::Vector3 position_)
{
	position = position_;
}

void Object3d::SetScale(Mathematics::Vector3 scale_)
{
	scale = scale_;
}

void Object3d::SetRotation(Mathematics::Vector3 rotation_)
{
	rotation = rotation_;
}

namespace Mathematics
{
	Vector3 GetWorldPosition(Object3d& transform)
	{
		// ���[���h���W������ϐ�
		Vector3 worldPos;
		// ���[���h�s��̕��s�ړ��������擾
		worldPos.x = transform.matWorld.m[3][0];
		worldPos.y = transform.matWorld.m[3][1];
		worldPos.z = transform.matWorld.m[3][2];

		return worldPos;
	}

	Matrix4 MakeWorldMatrix4(Object3d& transform)
	{
		Matrix4 matWorld = MyMathUtility::MakeIdentity();
		Matrix4 matScale, matRot, matTrans;

		// �X�P�[�����O�{��
		matScale = MyMathUtility::MakeScaling(transform.scale);
		// ��]�s��
		matRot = MyMathUtility::MakeRotation(transform.rotation);
		// �ړ���
		matTrans = MyMathUtility::MakeTranslation(transform.position);

		// matWorld�Ɋ|���Z
		matWorld = matScale * matRot * matTrans;

		if (transform.parent)
		{
			matWorld *= transform.parent->matWorld;
		}

		return matWorld;
	}
}
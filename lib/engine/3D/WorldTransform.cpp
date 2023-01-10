#include "WorldTransform.h"
#include "DirectX12Math.h"

Mathematics::Matrix4 WorldTransform::defaultProjectionMat = { 1.3579f, 0.0f, 0.0f, 0.0f, 0.0f, 2.4142f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0001f, 1.0f, 0.0f, 0.0f, -0.1000f, 0.0f };
Mathematics::Matrix4 WorldTransform::defaultViewMat = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f };

void WorldTransform::Initialize()
{
	HRESULT result;
	Mathematics::Matrix4 matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = MyMathUtility::MakeScaling(scale_);
	matRot = MyMathUtility::MakeIdentity();
	matRot = MyMathUtility::MakeRotation(rotation_);
	matTrans = MyMathUtility::MakeTranslation(translation_);

	// ���[���h�s��̍���
	matWorld_ = MyMathUtility::MakeIdentity();
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent_)
	{
		matWorld_ *= parent_->matWorld_;
	}

	// �萔�o�b�t�@�ɏ�������
	constMap_->matWorld = matWorld_ * defaultViewMat * defaultProjectionMat;
	constMap_->matWorld = matWorld_;
	constMap_
}

void WorldTransform::Update()
{
	
}

void WorldTransform::CreateConstBuff()
{
	HRESULT result;

	//�萔�o�b�t�@�̐���
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p

	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device_->GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void WorldTransform::TransferMatrix(Camera* camera)
{
	HRESULT result;
	Mathematics::Matrix4 matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = MyMathUtility::MakeScaling(scale_);
	matRot = MyMathUtility::MakeIdentity();
	matRot = MyMathUtility::MakeRotation(rotation_);
	matTrans = MyMathUtility::MakeTranslation(translation_);

	// ���[���h�s��̍���
	matWorld_ = MyMathUtility::MakeIdentity();
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	// �e�I�u�W�F�N�g�������
	if (parent_ != nullptr)
	{
		matWorld_ *= parent_->matWorld_;
	}

	const Mathematics::Matrix4 matView = camera->GetMatView();
	const Mathematics::Matrix4 matProjection = camera->GetMatProjection();

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataWorldTransform* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
	constMap->matWorld = matWorld_ * matView * matProjection;
	constBuff_->Unmap(0, nullptr);
}

// setter
void WorldTransform::SetTranslation(Mathematics::Vector3 translation)
{
	translation_ = translation;
}

void WorldTransform::SetScale(Mathematics::Vector3 scale)
{
	scale_ = scale;
}

void WorldTransform::SetRotation(Mathematics::Vector3 rotation)
{
	rotation_ = rotation;
}

ID3D12Resource* WorldTransform::GetConstBuff()
{
	return constBuff_.Get();
}

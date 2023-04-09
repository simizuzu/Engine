#include "WorldTransform.h"

void WorldTransform::Initialize()
{
	CreateConstBuffer();
}

void WorldTransform::Update(Camera* camera, bool billboradFlag)
{
	HRESULT result;
	Mathematics::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]���s�ړ��s��̌v�Z
	matScale = MyMathUtility::MakeScaling(scale_);
	matRot = MyMathUtility::MakeRotation(rotation_);
	matTrans = MyMathUtility::MakeTranslation(translation_);

	//���[���h�s��̍���
	matWorld = MyMathUtility::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent != nullptr)
	{
		matWorld *= parent->matWorld;
	}

	if (!billboradFlag)
	{
		const Mathematics::Matrix4 matView = camera->GetMatView();
		const Mathematics::Matrix4 matProjection = camera->GetMatProjection();

		//�萔�o�b�t�@�փf�[�^�]��
		ConstBufferDataB0* constMap = nullptr;
		result = constBuffer_->Map(0, nullptr, (void**)&constMap);
		assert(SUCCEEDED(result));
		constMap->mat = matWorld * matView * matProjection;
		constBuffer_->Unmap(0, nullptr);
	}
	else
	{
		//Mathematics::Matrix4 mat = camera->GetMatView();

		//mat.m[3][0] = 0;
		//mat.m[3][1] = 0;
		//mat.m[3][2] = 0;
		//mat.m[3][3] = 1;

		//matWorld = matScale * matRot * matTrans * camera->GetMatViewInverse() * camera->GetMatProjection();

		////�萔�o�b�t�@�փf�[�^�]��
		//ConstBufferDataB0* constMap = nullptr;
		//result = constBuffer_->Map(0, nullptr, (void**)&constMap);
		//assert(SUCCEEDED(result));
		//constMap->mat = matWorld;
		//constBuffer_->Unmap(0, nullptr);

		const Mathematics::Matrix4 matView = camera->GetMatView();
		const Mathematics::Matrix4 matProjection = camera->GetMatProjection();

		//�萔�o�b�t�@�փf�[�^�]��
		ConstBufferDataB0* constMap = nullptr;
		result = constBuffer_->Map(0, nullptr, (void**)&constMap);
		assert(SUCCEEDED(result));
		constMap->mat = matWorld * matView * matProjection;
		constBuffer_->Unmap(0, nullptr);
	}
}

D3D12_GPU_VIRTUAL_ADDRESS WorldTransform::GetGpuAddress()
{
	return constBuffer_->GetGPUVirtualAddress();
}

void WorldTransform::CreateConstBuffer()
{
	HRESULT result;

	//���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataB0) + 0xff) & ~0xff;//���_�f�[�^�S�̂̃T�C�Y
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
		IID_PPV_ARGS(&constBuffer_));
	assert(SUCCEEDED(result));
}

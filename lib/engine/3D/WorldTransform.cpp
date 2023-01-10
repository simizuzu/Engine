#include "WorldTransform.h"
#include "DirectX12Math.h"

Mathematics::Matrix4 WorldTransform::defaultProjectionMat = { 1.3579f, 0.0f, 0.0f, 0.0f, 0.0f, 2.4142f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0001f, 1.0f, 0.0f, 0.0f, -0.1000f, 0.0f };
Mathematics::Matrix4 WorldTransform::defaultViewMat = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f };

void WorldTransform::Initialize()
{
	HRESULT result;
	Mathematics::Matrix4 matScale, matRot, matTrans;

	// スケール、回転、平行移動行列の計算
	matScale = MyMathUtility::MakeScaling(scale_);
	matRot = MyMathUtility::MakeIdentity();
	matRot = MyMathUtility::MakeRotation(rotation_);
	matTrans = MyMathUtility::MakeTranslation(translation_);

	// ワールド行列の合成
	matWorld_ = MyMathUtility::MakeIdentity();
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	//親行列の指定がある場合は、掛け算する
	if (parent_)
	{
		matWorld_ *= parent_->matWorld_;
	}

	// 定数バッファに書き込み
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

	//定数バッファの生成
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用

	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff;//頂点データ全体のサイズ
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

	// スケール、回転、平行移動行列の計算
	matScale = MyMathUtility::MakeScaling(scale_);
	matRot = MyMathUtility::MakeIdentity();
	matRot = MyMathUtility::MakeRotation(rotation_);
	matTrans = MyMathUtility::MakeTranslation(translation_);

	// ワールド行列の合成
	matWorld_ = MyMathUtility::MakeIdentity();
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	// 親オブジェクトがあれば
	if (parent_ != nullptr)
	{
		matWorld_ *= parent_->matWorld_;
	}

	const Mathematics::Matrix4 matView = camera->GetMatView();
	const Mathematics::Matrix4 matProjection = camera->GetMatProjection();

	// 定数バッファへデータ転送
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

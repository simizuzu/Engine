#include "WorldTransform.h"
#include "DirectX12Math.h"

using namespace MyMathUtility;

void WorldTransform::Initialize()
{
	matWorld_ = MakeIdentity();
	CreateConstBuff();
	Map();
	TransferMatrix();
}

void WorldTransform::CreateConstBuff()
{
	dxCommon_->GetInstance()->CreateConstBuff(constMap_, constBuff_);
}

void WorldTransform::Map()
{
	// 定数バッファとのデータリンク
	HRESULT result = constBuff_->Map(0, nullptr, (void**)&constMap_);
	assert(SUCCEEDED(result));
}

void WorldTransform::TransferMatrix()
{
	constMap_->matWorld = matWorld_;
}

#include "WorldTransform.h"

void WorldTransform::Initialize()
{
}

void WorldTransform::CreateConstBuff(UINT sizeVB)
{

	dxCommon_->GetInstance()->CreateConstBuff(constMap_, constBuff_);
}

void WorldTransform::Map()
{

}

void WorldTransform::TransferMatrix()
{
}

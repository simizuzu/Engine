#include "FbxObject.h"

//静的メンバ変数の実態
ID3D12Device* FbxObject::device_ = nullptr;

void FbxObject::StaticInitialize(ID3D12Device* device)
{
	assert(device);

	FbxObject::device_ = device;
}

void FbxObject::Initialize()
{
	HRESULT result;

	CD3DX12_HEAP_PROPERTIES HEAPPROP = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC RESOURCEDESC = CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataTransformFbx) + 0xff) & ~0xff);
}

void FbxObject::CrateGrapicsPipeline()
{
}

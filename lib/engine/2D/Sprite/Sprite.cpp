#include "Sprite.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;

void Sprite::StaticInitialize()
{
}

void Sprite::PreDraw(ID3D12GraphicsCommandList* cmdList, BlendMode blendMode)
{
}

void Sprite::PostDraw()
{
}

void Sprite::Initialize()
{
	InitializeVertexBuff();
	InitializeShadeLoad();
}

void Sprite::Update()
{

}

void Sprite::Draw()
{
	// 頂点データ
	XMFLOAT3 vertices[] = {
		{-0.5f, -0.5f, 0.0f}, // 左下
		{-0.5f, +0.5f, 0.0f}, // 左上
		{+0.5f, -0.5f, 0.0f}, // 右下
	};
	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));
}

void Sprite::InitializeVertexBuff()
{

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{};		// ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // 頂点データのサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	HRESULT result = dxCommon_->GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,	// ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	// リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	// GPU状のバッファに対応した仮想メモリ(メインメモリ上)を取得
	XMFLOAT3* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// 全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	// 座標をコピー
	}
	// つながりを解除
	vertBuff->Unmap(0, nullptr);

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(XMFLOAT3);
}

void Sprite::InitializeShadeLoad()
{
	shader_->CreateSpriteShade();
	pipeline_->CreateSpritePipeline();
}
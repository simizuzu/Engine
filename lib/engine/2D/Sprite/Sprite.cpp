#include "Sprite.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* Sprite::device_ = nullptr;
UINT Sprite::descriptorSize_;
ID3D12GraphicsCommandList* Sprite::commandList_ = nullptr;
ComPtr<ID3D12RootSignature> Sprite::rootSignature_;
std::array<RootsigSetPip, 6> Sprite::pipelineState;
Mathematics::Matrix4 Sprite::matProjection_;
ComPtr<ID3DBlob> Sprite::vsBlob = nullptr;
ComPtr<ID3DBlob> Sprite::psBlob = nullptr;
Shader* Sprite::shader_ = nullptr;
Pipeline* Sprite::pipeline_ = nullptr;

void Sprite::StaticInitialize()
{
	device_ = DirectXCommon::GetInstance()->GetDevice();
	commandList_ = DirectXCommon::GetInstance()->GetCommandList();

	float width = static_cast<float>(WinApp::GetInstance()->window_width);
	float height = static_cast<float>(WinApp::GetInstance()->window_height);

	// デスクリプタサイズを取得
	descriptorSize_ = device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// 平行投影
	XMmatProjection_ = XMMatrixOrthographicOffCenterLH(
		0.0f, winApp_->GetInstance()->window_width,
		winApp_->GetInstance()->window_height, 0.0f,
		0.0f, 1.0f);

	shader_->CreateSpriteShade(vsBlob.Get(), psBlob.Get());

	for (int i = 0; i < pipelineState.size(); i++)
	{
		pipeline_->CreateSpritePipeline(vsBlob.Get(), psBlob.Get(), (BlendMode)i, device_, pipelineState);
	}
}

void Sprite::PreDraw()
{
	assert(Sprite::commandList_ == nullptr);

	// コマンドリスト //

}

void Sprite::PostDraw()
{
}

void Sprite::Initialize()
{
	InitializeVertexBuff();
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
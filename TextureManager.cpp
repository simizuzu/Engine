#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

void TextureManager::Initialize(DirectXCommon* directXCommon)
{
	HRESULT result;

	// メンバ変数に記録
	directXCommon_ = directXCommon;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = MaxSRVCount;
	// 設定を元にSRV用デスクリプタヒープを生成
	result = directXCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));
}

void TextureManager::LoadTexture(UINT texNumber, const wchar_t* filename)
{
	HRESULT result;

	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// ミップマップ生成
	result = DirectX::GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// 読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	// リソース設定
	D3D12_RESOURCE_DESC texResourceDesc{};
	texResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	texResourceDesc.Format = metadata.format;
	texResourceDesc.Width = metadata.width;
	texResourceDesc.Height = (UINT)metadata.height;
	texResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	texResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	texResourceDesc.SampleDesc.Count = 1;

	// テクスチャ用のバッファの生成
	result = directXCommon_->GetDevice()->CreateCommittedResource(
		&texHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&texResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff[texNumber]));

	// 全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップレベルを制定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = texBuff[texNumber]->WriteToSubresource(
			(UINT)i,
			nullptr,
			img->pixels,
			(UINT)img->rowPitch,
			(UINT)img->slicePitch
		);
		assert(SUCCEEDED(result));
	}
	
	// シェーダーリソースビューの作成
	// SRVヒープの先頭ハンドルを取得
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	// デスクリプタ1個分アドレスを進める
	srvHandle.ptr += directXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// シェーダーリソースビュー設定
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	// ヒープの2番目にシェーダーリソースビュー作成
	directXCommon_->GetDevice()->CreateShaderResourceView(
		texBuff[texNumber].Get(),	// ビューと関連付けるバッファ
		&srvDesc,		// テクスチャ設定情報
		srvHandle
	);
}

ID3D12Resource* TextureManager::GetTexBuff(UINT texNumber)
{
	// 指定した数字以下で動くように設定する
	assert(texNumber < MaxSRVCount);

	return texBuff[texNumber].Get();
}

void TextureManager::SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList)
{
	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void TextureManager::SetGraphicsRootDesCriptorTable(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber)
{
	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// シェーダリソースビューをセット
	commandList->SetGraphicsRootDescriptorTable(rootPrameterIndex, srvGpuHandle);
}

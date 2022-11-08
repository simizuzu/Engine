#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

uint32_t TextureManager::Load(const std::string& fileName)
{
	return TextureManager::GetInstance()->LoadTexture(fileName);
}

void TextureManager::Initialize(DirectXCommon* directXCommon)
{
	HRESULT result;

	// メンバ変数に記録
	directXCommon_ = directXCommon;

	// デスクリプタレンジの設定
	descriptorRange.NumDescriptors = 1; // 1度の描画に使うテクスチャの数
	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	descriptorRange.BaseShaderRegister = 0; // レジスタ番号
	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = MaxSRVCount;
	// 設定を元にSRV用デスクリプタヒープを生成
	result = directXCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	// ヒープ設定
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
}

uint32_t TextureManager::LoadTexture(const std::string& fileName)
{
	if (texCount > 1024)
	{
		assert(0);
	}

	TextureData tmp{};

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	ScratchImage mipChain{};

	tmp.srvHeap = srvHeap;
	tmp.descriptorRange = descriptorRange;

	wchar_t wfilepath[256];

	MultiByteToWideChar(CP_ACP, 0, fileName.c_str(), -1, wfilepath, _countof(wfilepath));

	// WICテクスチャのロード
	HRESULT result = LoadFromWICFile(
		wfilepath,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// ミップマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(),
		scratchImg.GetImageCount(),
		scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// 読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = MakeSRGB(metadata.format);

	// リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;
	textureResourceDesc.Height = (UINT)metadata.height;
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	// テクスチャバッファの生成
	result = directXCommon_->GetDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(tmp.texBuff.ReleaseAndGetAddressOf()));

	// 全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		// ミップマップレベルを指定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = tmp.texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // 全領域へコピー
			img->pixels,          // 元データアドレス
			(UINT)img->rowPitch,  // 1ラインサイズL"Basic
			(UINT)img->slicePitch // 1枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	tmp.srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = directXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// ハンドルのポインタずらし
	srvHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;
	tmp.srvGpuHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;

	// シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metadata.mipLevels);

	// ハンドルの指す位置にシェーダーリソースビュー生成
	directXCommon_->GetDevice()->CreateShaderResourceView(tmp.texBuff.Get(), &srvDesc, srvHandle);

	tmp.width = metadata.width;
	tmp.height = metadata.height;

	texCount++;
}

void TextureManager::SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList)
{
	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void TextureManager::SetShaderResourceView(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber)
{
	TextureData tmp{};

	UINT incrementSize = directXCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	tmp.srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	// ハンドルのポインタずらし
	srvHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;
	tmp.srvGpuHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

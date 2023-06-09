#include "TextureManager.h"
#include <cassert>

TextureManager* TextureManager::textureManager_ = nullptr;
std::string TextureManager::DefaultTextureDirectoryPath = "Resource/";

TextureData TextureManager::Load(const std::string& fileName)
{
	return TextureManager::GetInstance()->LoadTexture(fileName);
}

void TextureManager::Initialize(DirectXCommon* directXCommon)
{
	HRESULT result;

	// メンバ変数に記録
	dxCommon_ = directXCommon;

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
	textureHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
}

TextureData TextureManager::LoadTexture(const std::string& fileName)
{
	if (texCount > 1024)
	{
		assert(0);
	}

	TextureData tmp{};

	DirectX::TexMetadata metadata{};
	DirectX::ScratchImage scratchImg{};
	DirectX::ScratchImage mipChain{};

	tmp.srvHeap = srvHeap;
	tmp.descriptorRange = descriptorRange;

	wchar_t wfilepath[256];

	MultiByteToWideChar(CP_ACP, 0, fileName.c_str(), -1, wfilepath, _countof(wfilepath));

	// WICテクスチャのロード
	HRESULT result = LoadFromWICFile(
		wfilepath,
		DirectX::WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	// ミップマップ生成
	result = GenerateMipMaps(
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

	tmp.texBuff = CreateTexBuff(metadata, scratchImg);

	tmp.srvGpuHandle = CreateShaderResourceView(tmp.texBuff.Get(), metadata);

	tmp.width = metadata.width;
	tmp.height = metadata.height;

	texCount++;

	return tmp;
}

Microsoft::WRL::ComPtr<ID3D12Resource> TextureManager::CreateTexBuff(DirectX::TexMetadata& metadata, DirectX::ScratchImage& scratchImg)
{
	Microsoft::WRL::ComPtr<ID3D12Resource> resource;
	HRESULT result;

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
	result = dxCommon_->GetDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));

	// 全ミップマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		// ミップマップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = resource->WriteToSubresource(
			(UINT)i,
			nullptr,              // 全領域へコピー
			img->pixels,          // 元データアドレス
			(UINT)img->rowPitch,  // 1ラインサイズL"Basic
			(UINT)img->slicePitch // 1枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	return resource;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::CreateShaderResourceView(ID3D12Resource* texBuff, DirectX::TexMetadata& metadata)
{
	//SRVヒープの先頭ハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = dxCommon_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;
	gpuHandle.ptr += static_cast<UINT64> (texCount) * incrementSize;

	// シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metadata.mipLevels);

	// ハンドルの指す位置にシェーダーリソースビュー生成
	dxCommon_->GetDevice()->CreateShaderResourceView(texBuff, &srvDesc, cpuHandle);

	return gpuHandle;
}

ID3D12Resource* TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, ID3D12Device* device, ID3D12GraphicsCommandList* cmdList)
{
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(device, mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresources.size()));
	ID3D12Resource* intermediaResource = CreateBufferResource(device, subresources);
	UpdateSubresources(cmdList, texture, intermediaResource, 0, 0, UINT(subresources.size()), subresources.data());

	//D3D12_RESOURCE_STATE_COPY_DESTからD3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変換する
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	cmdList->ResourceBarrier(1,&barrier);
	return intermediaResource;
}

void TextureManager::Delete()
{
	delete textureManager_;
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

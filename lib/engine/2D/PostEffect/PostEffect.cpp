#include "PostEffect.h"

const float PostEffect::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

PostEffect::PostEffect()
{

}

void PostEffect::Initialize()
{
	CreateTextureBuff();
	CreateSRVDesc();
	CreateRTVDesc();
	CreateDepthBuff();
	CreateDSVDesc();
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	ID3D12DescriptorHeap* ppHeaps[] = { descHeapSRV.Get() };

	cmdList->SetGraphicsRootDescriptorTable(1, descHeapSRV->GetGPUDescriptorHandleForHeapStart());
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更（シェーダーリソース→描画可能）
	CD3DX12_RESOURCE_BARRIER CHANGE_RENDER_TARGET =
		CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(), D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
	cmdList->ResourceBarrier(1, &CHANGE_RENDER_TARGET);

	//レンダーターゲットビュー用ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//深度ステンシルビュー用デスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//ビューポートの設定
	CD3DX12_VIEWPORT VIEWPORT =
		CD3DX12_VIEWPORT(0.0f, 0.0f, winApp_->window_width, winApp_->window_height);
	cmdList->RSSetViewports(1, &VIEWPORT);
	//シザリング矩形の設定
	CD3DX12_RECT RECT =
		CD3DX12_RECT(0, 0, winApp_->window_width, winApp_->window_height);
	cmdList->RSSetScissorRects(1, &RECT);

	//全画面クリア
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリアを変更（描画可能→シェーダーリソース）
	CD3DX12_RESOURCE_BARRIER CHANGE_PIXEL_SHADER_RESOURCE =
		CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	cmdList->ResourceBarrier(1, &CHANGE_PIXEL_SHADER_RESOURCE);
}

void PostEffect::CreateVertexData()
{
	HRESULT result;

	result = device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPos))
	)
}

void PostEffect::CreateTextureBuff()
{
	HRESULT result;
	winApp_ = winApp_->GetInstance();

	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texturesDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		winApp_->window_width,
		winApp_->window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	//テクスチャバッファの生成
	CD3DX12_HEAP_PROPERTIES HEAP_PROPERTIES =
		CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	CD3DX12_CLEAR_VALUE CLEAR_VALUE = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);

	result = device_->CreateCommittedResource(
		&HEAP_PROPERTIES,
		D3D12_HEAP_FLAG_NONE,
		&texturesDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&CLEAR_VALUE,
		IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	{	//テクスチャを赤クリア
		//画像数(1280 * 720)
		const UINT pixelCount = winApp_->window_width * winApp_->window_height;
		//画像1行分のデータサイズ
		const UINT rowPitch = sizeof(UINT) * winApp_->window_width;
		//画像全体のデータサイズ
		const UINT depthPitch = rowPitch * winApp_->window_height;
		//画像イメージ
		UINT* img = new UINT[pixelCount];
		for (int i = 0; i < pixelCount; i++)
		{
			img[i] = 0xff0000ff;
		}

		//テクスチャバッファにデータ転送
		result = texBuff->WriteToSubresource(0, nullptr,
			img, rowPitch, depthPitch);
		assert(SUCCEEDED(result));
		delete[] img;
	}
}

void PostEffect::CreateSRVDesc()
{
	HRESULT result;
	//SRV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;
	//SRV用デスクリプタヒープを生成
	result = device_->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));

	//SRV設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープにSRV作成
	device_->CreateShaderResourceView(texBuff.Get(),
		&srvDesc,
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()
	);
}

void PostEffect::CreateRTVDesc()
{
	HRESULT result;
	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc = {};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV用デスクリプタヒープを生成
	result = device_->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	//レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//シェーダーの計算結果をSRGBに変換して書き込む
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//デスクリプタヒープ二RTV作成
	device_->CreateRenderTargetView(texBuff.Get(),
		&renderTargetViewDesc,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart()
	);
}

void PostEffect::CreateDSVDesc()
{
	HRESULT result;
	//深度バッファリソース設定
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			winApp_->window_width,
			winApp_->window_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);

	//深度バッファの生成
	CD3DX12_HEAP_PROPERTIES HEAP_PROPERTIES = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_CLEAR_VALUE CLEAR_VALUE = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);

	result = device_->CreateCommittedResource(
		&HEAP_PROPERTIES,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&CLEAR_VALUE,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));
}

void PostEffect::CreateDepthBuff()
{
	HRESULT result;
	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	descHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを生成
	result = device_->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device_->CreateDepthStencilView(depthBuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart());
}

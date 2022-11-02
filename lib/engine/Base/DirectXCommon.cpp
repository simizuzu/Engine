#include "DirectXCommon.h"

void DirectXCommon::Initialize(WinApp* winApp)
{
#ifdef _DEBUG
	EnableDebugLayer();
	//BreakOnSeverity();
#endif
	// NULL検出
	assert(winApp);
	// メンバ変数に記録
	this->winApp = winApp;

	// デバイスの生成
	InitializeDevice();
	// コマンド関連の初期化
	InitializeCommand();
	// スワップチェーンの初期化
	InitializeSwapChain();
	// レンダーターゲットビューの初期化
	InitializeRTV();
	// 深度バッファの初期化
	InitializeDepthBuffer();
	// フェンスの初期化
	InitializeFence();
}

#pragma region 各初期化
void DirectXCommon::InitializeDevice()
{
	// 対応レベルの配列
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT result;

	// デバックレイヤーをオンに
	ComPtr<ID3D12Debug> debugController;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}

	// DXGIファクトリーの生成
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// アダプターの列挙用
	std::vector <ComPtr<IDXGIAdapter4>>adapters;
	// ここに特定の名前を持つアダプターオブジェクトが入る
	ComPtr<IDXGIAdapter4> tmpAdapter;

	// パフォーマンスが高いものから順に、すべてのアダプターを列挙する
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {
		//動的配列に追加する
		adapters.push_back(tmpAdapter);
	}

	// 妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		// アダプターの情報を取得する
		adapters[i]->GetDesc3(&adapterDesc);

		// ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			// デバイスを採用してループを抜ける
			tmpAdapter = adapters[i];
			break;
		}
	}

	// Direct3Dデバイスの初期化
	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		// 採用したアダプターでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&device));
		if (result == S_OK) {
			// デバイスを生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}
}

void DirectXCommon::InitializeCommand()
{
	HRESULT result;

	// コマンドアロケータの生成
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));

	// コマンドリストを生成
	result = device->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));

	// コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{}; //構造体の中身を0でクリアしている
	// コマンドキューを生成
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeSwapChain()
{
	HRESULT result;
	WinApp* winApp = WinApp::GetInstance();
	ComPtr<IDXGISwapChain1> swapChain1;

	// スワップチェーンの設定
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// スワップチェーン生成
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(), 
		winApp->GetHwnd(),
		&swapChainDesc, 
		nullptr, 
		nullptr, 
		&swapChain1);

	assert(SUCCEEDED(result));

	// 生成したIDXGISwapChain1のオブジェクトをIDXGISwapChain4に変換する
	swapChain1.As(&swapChain);
}

void DirectXCommon::InitializeRTV()
{
	//デスクリプタヒープの設定
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; //レンダーターゲットビュー
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;
	//デスクリプタヒープの生成
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	//バックバッファ
	backBuffers.resize(swapChainDesc.BufferCount);

	//スワップチェーンの全てのバッファについて処理する
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//スワップチェーンからバッファを取得
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//デスクリプタヒ－プのハンドルを取得
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//裏か表かでアドレスがずれる
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//レンダーターゲットビューの設定
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//シェーダーの計算結果をSRGBに変換して書き込む
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//レンダーターゲットビューの生成
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::InitializeDepthBuffer()
{
	HRESULT result;
	this->winApp = winApp;

	// 深度バッファリソース設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = winApp->window_width;   //レンダーターゲットに合わせる
	depthResourceDesc.Height = winApp->window_height; //レンダーターゲットに合わせる
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // デプスステンシル
	// 深度地用ヒーププロパティ
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	// 深度地のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f; // 深度地1.0f（最大値）でクリア
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT; // 深度地フォーマット

	// 深度バッファ生成
	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度地書き込みに使用
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));

	// 深度ビュー(DSV)用デスクリプタヒープ作成
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	dsvHeapDesc.NumDescriptors = 1; // 深度ビューは1つ
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	assert(SUCCEEDED(result));

	// 深度ビュー(DSV)作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度地フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff,
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart());
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeFence()
{
	HRESULT result;
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}
#pragma endregion

#pragma region エラーメッセージの抑制
void DirectXCommon::EnableDebugLayer()
{
	//デバックレイヤーをオンに
	ID3D12Debug1* debugController;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
}

//void DirectXCommon::BreakOnSeverity()
//{
//	ID3D12InfoQueue* infoQueue;
//	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
//	{
//		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);	// 不正時(エラーより上)に止まる
//		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);		// エラー時に止まる
//		infoQueue->Release();
//	}
//
//	// 抑制するエラー
//	D3D12_MESSAGE_ID denyIds[] = {
//		/*
//		 * Windows11でのDXGIデバックレイヤーとD12デバックレイヤーの相互作用バグによるエラーメッセージ
//		 * https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
//		 */
//		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
//	};
//	// 抑制する表示レベル
//	D3D12_MESSAGE_SEVERITY severiries[] = { D3D12_MESSAGE_SEVERITY_INFO };
//	D3D12_INFO_QUEUE_FILTER filter{};
//	filter.DenyList.NumIDs = _countof(denyIds);
//	filter.DenyList.pIDList = denyIds;
//	filter.DenyList.NumSeverities = _countof(severiries);
//	filter.DenyList.pSeverityList = severiries;
//	// 指定したエラーの表示を抑制する
//	infoQueue->PushStorageFilter(&filter);
//}
#pragma endregion

#pragma region ゲッター
ID3D12Device* DirectXCommon::GetDevice()
{
	return device.Get();
}

IDXGIFactory7* DirectXCommon::GetDxgiFactory()
{
	return dxgiFactory.Get();
}

IDXGISwapChain4* DirectXCommon::GetSwapChain()
{
	return swapChain.Get();
}

ID3D12CommandAllocator* DirectXCommon::GetCmdAllocator()
{
	return commandAllocator.Get();
}

ID3D12GraphicsCommandList* DirectXCommon::GetCommandList()
{
	return commandList.Get();
}

ID3D12CommandQueue* DirectXCommon::GetCommandQueue()
{
	return commandQueue.Get();
}

ID3D12DescriptorHeap* DirectXCommon::GetRtvHeap()
{
	return rtvHeap.Get();
}

ID3D12Fence* DirectXCommon::GetFence()
{
	return fence.Get();
}
#pragma endregion
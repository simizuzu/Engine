#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <cassert>
#include <vector>

#include "WinApp.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class DirectXCommon
{
private:
	// テンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// DirectX12デバイス
	ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	// バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// 深度テストの設定
	ID3D12Resource* depthBuff = nullptr;
	ID3D12DescriptorHeap* dsvHeap = nullptr;
	// フェンスの生成
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	// ゲッター
	ID3D12Device* GetDevice();
	IDXGIFactory7* GetDxgiFactory();
	IDXGISwapChain4* GetSwapChain();
	ID3D12CommandAllocator* GetCmdAllocator();
	ID3D12GraphicsCommandList* GetCommandList();
	ID3D12CommandQueue* GetCommandQueue();
	ID3D12DescriptorHeap* GetRtvHeap();
	ID3D12Fence* GetFence();

private: // 各初期化
	/// <summary>
	/// デバイスの初期化
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// コマンド関連の初期化
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// スワップチェーンの初期化
	/// </summary>
	void InitializeSwapChain();
	/// <summary>
	/// レンダーターゲットビューの初期化
	/// </summary>
	void InitializeRTV();
	/// <summary>
	/// 深度バッファの初期化
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// フェンスの初期化
	/// </summary>
	void InitializeFence();

private: // エラーメッセージの抑制
	/// <summary>
	/// デバッグレイヤーを有効にする
	/// </summary>
	void EnableDebugLayer();
	/// <summary>
	/// デバックレイヤー時に止める処理(Windows10版)
	/// </summary>
	void BreakOnSeverity();

private:
	WinApp* winApp = nullptr;
};


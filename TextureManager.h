#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <wrl.h>
#include <DirectXTex.h>

/// <summary>
/// テクスチャマネージャ
/// </summary>
class TextureManager
{
public: // エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 定数
	static const int MaxSRVCount = 512; // テクスチャの最大枚数

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXCommon"></param>
	void Initialize(DirectXCommon* directXCommon);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="texNumber">テクスチャ番号</param>
	/// <param name="filename">テクスチャファイル名</param>
	void LoadTexture(UINT texNumber, const wchar_t* filename);

	/// <summary>
	/// テクスチャバッファ取得
	/// </summary>
	/// <param name="texNumber"></param>
	/// <returns>テクスチャバッファ</returns>
	ID3D12Resource* GetTexBuff(UINT texNumber);

	/// <summary>
	/// デスクリプタヒープをセット（グラフィックスコマンド）
	/// </summary>
	/// <param name="commandList">コマンドリスト</param>
	void SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// SRVをセット（グラフィックスコマンド）
	/// </summary>
	/// <param name="commandList">コマンドリスト</param>
	/// <param name="rootPrameterIndex">ルートパラメータの番号</param>
	/// <param name="texNumber">テクスチャ番号</param>
	void SetGraphicsRootDesCriptorTable(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber);

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private: // メンバ変数
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	ComPtr<ID3D12Resource> texBuff[MaxSRVCount];

	//ComPtr<ID3D12Resource> texBuff;

	// GPUデスクリプタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange;

	D3D12_HEAP_PROPERTIES texHeapProp;

	DirectXCommon* directXCommon_ = nullptr;
};


#pragma once

#include "DirectXCommon.h"

#include <d3d12.h>
#include <wrl.h>
#include <DirectXTex.h>
#include <array>

struct TextureData
{
	// テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//GPUデスクリプタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle;
	// デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange;

	// 横幅
	size_t width = 0;
	// 縦幅
	size_t height = 0;
};

/// <summary>
/// テクスチャマネージャ
/// </summary>
class TextureManager
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 定数
	static const size_t MaxSRVCount = 1024; // テクスチャの最大枚数

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="directXCommon"></param>
	void Initialize(DirectXCommon* directXCommon);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="filename">テクスチャファイル名</param>
	void LoadTexture(const std::string& fileName);

	/// <summary>
	/// デスクリプタヒープをセット（グラフィックスコマンド）
	/// </summary>
	/// <param name="commandList">コマンドリスト</param>
	void SetGrapihcsSrvHeaps(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// シェーダーリソースビューをセット
	/// </summary>
	/// <param name="commandList">コマンドリスト</param>
	/// <param name="rootPrameterIndex">ルートパラメータ</param>
	/// <param name="texNumber">テクスチャ番号</param>
	void SetShaderResourceView(ID3D12GraphicsCommandList* commandList, UINT rootPrameterIndex, UINT texNumber);

	// インスタンス
	static TextureManager* GetInstance();

	// Getter
	ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }

private: // メンバ変数
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	D3D12_HEAP_PROPERTIES textureHeapProp;

	// テクスチャ数
	UINT texCount;

	DirectXCommon* directXCommon_ = nullptr;

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(const TextureManager&) = delete;
};


#pragma once

#include <d3d12.h>
#include <wrl.h>

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
	void Initialize();

private: // メンバ変数
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	ComPtr<ID3D12Resource> spriteTexBuff[MaxSRVCount];
};


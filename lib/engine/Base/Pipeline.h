#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <array>
#include "DirectXCommon.h"
#include "EngineUtility.h"
#include "AvoidWarning.h"

class Pipeline
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数

	/// <summary>
	/// パイプライン呼び出し用関数(スプライト)
	/// </summary>
	static void CreateSpritePipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend,ID3D12Device* device, std::array<RootsigSetPip,6>&pipeline);

	/// <summary>
	/// パイプライン呼び出し用関数(3Dオブジェクト)
	/// </summary>
	static void CreateObjPipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend, ID3D12Device* device, RootsigSetPip& pipeline);

	/// <summary>
	/// パイプライン呼び出し用関数(パーティクル)
	/// </summary>
	static void CreatePaticlePipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, ID3DBlob* gsBlob, ID3D12Device* device, RootsigSetPip& pipeline);

	static void CreatePostEffectPipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, ID3D12Device* device, RootsigSetPip& pipeline);

private: // メンバ変数

	// クラス呼び出し
	DirectXCommon* dxCommon_ = nullptr;
};


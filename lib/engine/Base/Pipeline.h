#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <array>
#include "DirectXCommon.h"

enum class BlendMode
{
	None,	// ブレンド無し
	Alpha,	// アルファ
	Add,	// 加算
	Sub,	// 減算
	Mul,	// 乗算
	Inv,	// 色反転
};

struct RootsigSetPip
{
	// ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	// パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

class Pipeline
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数

	/// <summary>
	/// パイプライン呼び出し用関数(スプライト)
	/// </summary>
	static void CreateSpritePipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend,ID3D12Device* device, std::array<RootsigSetPip,6>&pipeline);

	static void CreateObjPipeline(ID3DBlob* vsBlob, ID3DBlob* psBlob, BlendMode blend, ID3D12Device* device);

public:
	void SetBlendMode(int blendMode) { };

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;

	// クラス呼び出し
	DirectXCommon* dxCommon_ = nullptr;
};


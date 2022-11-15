#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Sprite.h"
#include "DirectXCommon.h"

class Pipeline
{
public:
	enum class BlendMode
	{
		None,	// ブレンド無し
		Alpha,	// アルファ
		Add,	// 加算
		Sub,	// 減算
		Mul,	// 乗算
		Inv,	// 色反転

		CountOfBlendMode, // 最大ブレンドモード数
	};

public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数

	/// <summary>
	/// パイプライン呼び出し用関数(スプライト)
	/// </summary>
	void CreateSpritePipeline();

	/// <summary>
	/// パイプライン呼び出し用関数(モデル)
	/// </summary>
	//void CreateModelPipeline();

public:
	void SetBlendMode(int blendMode) { };

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステート
	ComPtr<ID3D12PipelineState> pipelineState;
	// ブレンドデスク
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc;

	// クラス呼び出し
	Sprite* sprite_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
};


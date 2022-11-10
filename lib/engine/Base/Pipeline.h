#pragma once
#include <d3d12.h>
#include <wrl.h>
#include "Sprite.h"
#include "DirectXCommon.h"

class Pipeline
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// パイプライン呼び出し用関数(スプライト)
	/// </summary>
	void CreateSpritePipeline();

	/// <summary>
	/// パイプライン呼び出し用関数(モデル)
	/// </summary>
	void CreateModelPipeline();

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> vsBlob;
	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;
	// エラーオブジェクト
	ComPtr<ID3DBlob> errorBlob;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	// パイプラインステート
	ComPtr<ID3D12PipelineState> pipelineState;

	// クラス呼び出し
	Sprite* sprite_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
};


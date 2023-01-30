#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"

// 定数バッファ用データ構造体
struct ConstBufferDataB0
{
	Mathematics::Matrix4 mat;	// 3D変換行列
};

struct ConstBufferDataViewProjection
{
	// ワールド行列
	Mathematics::Matrix4 world;
	// ワールド座標
	Mathematics::Matrix4 matWorld;

	// ワールド → ビュー変換行列
	Mathematics::Matrix4 view;
	// ビュー → プロジェクション変換行列
	Mathematics::Matrix4 projection;
	// カメラ座標（ワールド座標）
	Mathematics::Vector3 cameraPos;
};

struct ViewProjection
{
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	// マッピング済みアドレス
	ConstBufferDataViewProjection* constBuffMap = nullptr;
};

struct VertexPosNormalUv
{
	Mathematics::Vector3 pos;		// xyz座標
	Mathematics::Vector3 normal;	// 法線ベクトル
	Mathematics::Vector2 uv;		// uv座標
};

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

struct TextureData
{
	// テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//GPUデスクリプタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle{};
	// デスクリプタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange{};

	// 横幅
	size_t width = 0;
	// 縦幅
	size_t height = 0;
};
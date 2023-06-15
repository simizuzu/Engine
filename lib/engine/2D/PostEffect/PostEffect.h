#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>
#include <d3dx12.h>

#include "DirectX12Math.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include "Sprite.h"
#include "TextureManager.h"
#include "DirectXCommon.h"

struct VertexPosUv
{
	MyMath::Vector3 pos;
	MyMath::Vector2 uv;
};

class PostEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

	void Initialize();

	/// <summary>
	/// 描画コマンドの実行
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList, WinApp* winApp);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

private:
	/// <summary>
	/// 頂点データの生成
	/// </summary>
	void CreateVertexData(ID3D12Device* device);

	/// <summary>
	/// テクスチャ生成
	/// </summary>
	void CreateTextureBuff(ID3D12Device* device, WinApp* winApp);

	/// <summary>
	/// SRV作成
	/// </summary>
	void CreateSRVDesc(ID3D12Device* device);

	/// <summary>
	/// RTV作成
	/// </summary>
	void CreateRTVDesc(ID3D12Device* device);

	/// <summary>
	/// DSV作成
	/// </summary>
	void CreateDSVDesc(ID3D12Device* device, WinApp* winApp);

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	void CreateDepthBuff(ID3D12Device* device);

private:
	//デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	//SRV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//RTV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV用デスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	static const float clearColor[4];

	std::shared_ptr<WinApp> winApp_;
	std::shared_ptr<DirectXCommon> dxCommon;
};


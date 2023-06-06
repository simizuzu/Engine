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

private:
	/// <summary>
	/// テクスチャ生成
	/// </summary>
	void CreateTextureBuff();

	/// <summary>
	/// SRV作成
	/// </summary>
	void CreateSRVDesc();

	/// <summary>
	/// RTV作成
	/// </summary>
	void CreateRTVDesc();

	/// <summary>
	/// DSV作成
	/// </summary>
	void CreateDSVDesc();

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	void CreateDepthBuff();

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


	WinApp* winApp_ = nullptr;
};


#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <vector>
#include <string>
#include <wrl.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include "TextureManager.h"
#include "DirectXCommon.h"

struct VertexPosNormalUv
{
	Mathematics::Vector3 pos;		// xyz座標
	Mathematics::Vector3 normal;	// 法線ベクトル
	Mathematics::Vector2 uv;		// uv座標
};

struct Material
{
	std::string name;				// マテリアル名
	Mathematics::Vector3 ambient;	// アンビエント影響度
	Mathematics::Vector3 diffuse;	// ディフューズ影響度
	Mathematics::Vector3 specular;	// スペキュラー影響度
	float alpha;					// アルファ
	std::string textureFilename;	// テクスチャファイル名

	// コンストラクタ
	Material() {
		ambient = { 0.3f,0.3f,0.3f };
		diffuse = { 0.0f,0.0f,0.0f };
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};

/// <summary>
/// 3Dモデル
/// </summary>
class Model
{
public:
	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		Mathematics::Vector3 ambient;	// アンビエント係数
		float pad1;						// パディング
		Mathematics::Vector3 diffuse;	// ディフューズ係数
		float pad2;						// パディング
		Mathematics::Vector3 specular;	// スペキュラー係数
		float alpha;					// アルファ
	};

public:
	/// <summary>
	/// OBJファイルから3Dモデルを読み込む
	/// </summary>
	/// <returns>モデル</returns>
	static Model* LoadFromObj(const std::string& modelname);

	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	/// <param name="rootParamIndexMaterial">マテリアル用ルートパラメータ番号</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	static void SetDevice(ID3D12Device* device) { Model::device = device; };

private: // 静的メンバ変数
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// テクスチャバッファ
	static Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// シェーダリソースビューのハンドル(CPU)
	D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// シェーダリソースビューのハンドル(GPU)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// デスクリプタヒープ
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	static std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	static std::vector<unsigned short> indices;
	// マテリアル
	static Material material;

private: // メンバ変数
	// 定数バッファ（マテリアル）
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// テクスチャデータ
	TextureData textureData;
private:
	/// <summary>
	/// OBJファイルから3Dモデルを読み込む
	/// </summary>
	void LoadFromOBJInternal(const std::string& modelname);

	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// 各種バッファ生成
	/// </summary>
	void CreateBuffers();

	/// <summary>
	/// 頂点データ全体のサイズ
	/// </summary>
	void CreateVBSize();

	/// <summary>
	/// インデックスデータ全体のサイズ
	/// </summary>
	void CreateIBSize();
};


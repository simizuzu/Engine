#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <vector>
#include <string>
#include <wrl.h>
#include <unordered_map>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"

#include "TextureManager.h"
#include "DirectXCommon.h"
#include "EngineUtility.h"

struct Material
{
	std::string name;				// マテリアル名
	MyMath::Vector3 ambient;	// アンビエント影響度
	MyMath::Vector3 diffuse;	// ディフューズ影響度
	MyMath::Vector3 specular;	// スペキュラー影響度
	float alpha;					// アルファ
	std::string textureFilename;	// テクスチャファイル名
	float shininess = 1.0f;
	char pad[4];

	// コンストラクタ
	Material() {
		ambient = { 0.3f,0.3f,0.3f };
		diffuse = { 0.0f,0.0f,0.0f };
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};

#pragma region FBX
//ボーンの最大数
constexpr int MAX_BONES = 128;
constexpr int MAX_BONE_INDICES = 4;

struct PosNormUvTangeColSkin
{
	MyMath::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // 位置座標
	MyMath::Vector3 normal; // 法線
	MyMath::Vector2 uv; // uv座標
	MyMath::Vector3 tangent; // 接空間
	MyMath::Vector4 color; // 頂点色

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// ボーンの番号
	std::array<float, MAX_BONE_INDICES> boneWeight;	// ボーンの重み
};

struct PosNormUvTangeCol
{
	MyMath::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // 位置座標
	MyMath::Vector3 normal; // 法線
	MyMath::Vector2 uv; // uv座標
	MyMath::Vector3 tangent; // 接空間
	MyMath::Vector4 color; // 頂点色
};

struct PosNormSkin
{
	MyMath::Vector4 position; // 位置座標
	MyMath::Vector3 normal; // 法線

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// ボーンの番号
	std::array<float, MAX_BONE_INDICES> boneWeight;	// ボーンの重み
};

struct PosNorm
{
	MyMath::Vector4 position; // 位置座標
	MyMath::Vector3 normal; // 法線
};
//定数バッファ用データ構造体(スキニング)
struct SkinData
{
	std::vector<MyMath::Matrix4> bones;
};

struct SkinComputeInput
{
	std::vector<PosNormSkin> vertices;
	SkinData bone;
};

struct Node
{
	//名前
	std::string name;
	//ローカル変形行列
	MyMath::Matrix4 transform;
	//グローバル変形行列
	MyMath::Matrix4 globalTransform;
	//親ノード
	Node* parent = nullptr;
	//子ノード
	std::vector<Node>childrens;
};

struct Bone
{
public:
	//名前
	std::string name;

	MyMath::Matrix4 matrix = {};

	MyMath::Matrix4 offsetMatirx = {};

	UINT index = 0;

	Bone() = default;
	~Bone() = default;

private:
	char PADING[4] = {};
};

struct BoneData
{
	//ボーンデータ
	std::array<MyMath::Matrix4, MAX_BONES> boneMat;
};

class ModelMesh
{
public:

	//名前
	std::string name;

	//名前
	std::string nodeName;

	//頂点データの配列
	std::vector<PosNormUvTangeColSkin> vertices;

	//インデックスの配列
	std::vector<uint32_t> indices;

	//テクスチャ
	std::vector <std::string> textures;

	//テクスチャ
	std::vector <std::string> texturesNormal;

	std::vector<Bone> vecBones;

	std::vector<MyMath::Matrix4> deformationMat;

	//有効
	bool enable = false;
	char PADING[3]{};

	// カラー
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	char PADING1[4]{};

	// マテリアル
	Material material;

	Node* node = nullptr;

	//描画頂点データ
	std::vector<PosNormUvTangeCol> vertice;

	SkinComputeInput skinComputeInput;

	SkinData skinData;

	BoneData bonedata;

	bool dirtyFlag;
	char PADING2[7]{};

public:


};

class fbxModel
{
public:
	bool isAnimetion;
	char pad1[7];

	//モデル名
	std::string name;
	//ノード配列
	std::vector<ModelMesh> meshes;
};
#pragma endregion 

#pragma region OBJ

/// <summary>
/// 3Dモデル
/// </summary>
class Model
{
public:
	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		MyMath::Vector3 ambient;	// アンビエント係数
		float pad1;						// パディング
		MyMath::Vector3 diffuse;	// ディフューズ係数
		float pad2;						// パディング
		MyMath::Vector3 specular;	// スペキュラー係数
		float alpha;					// アルファ
	};

public:
	/// <summary>
	/// OBJファイルから3Dモデルを読み込む
	/// </summary>
	/// <returns>モデル</returns>
	static Model* LoadFromObj(const std::string& modelname, bool smoothing = false);

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
	void Draw(ID3D12GraphicsCommandList* cmdList);

	static void SetDevice(ID3D12Device* device) { Model::device = device; };

private: // 静的メンバ変数
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// テクスチャバッファ
	 Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// シェーダリソースビューのハンドル(CPU)
	D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// シェーダリソースビューのハンドル(GPU)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// デスクリプタヒープ
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファビュー
	 D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	 D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	 std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	 std::vector<unsigned short> indices;
	// マテリアル
	 Material material;

private: // メンバ変数
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	// 定数バッファ（マテリアル）
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1;
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//インデックスバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// テクスチャデータ
	TextureData textureData;

	//頂点法線スムージング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;

private:
	/// <summary>
	/// OBJファイルから3Dモデルを読み込む
	/// </summary>
	void LoadFromOBJInternal(const std::string& modelname, bool smoothing);

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

	/// <summary>
	/// 頂点データの数を取得
	/// </summary>
	/// <returns>頂点データの取得</returns>
	inline size_t GetVertexCount();

	/// <summary>
	/// エッジ平滑化データの追加
	/// </summary>
	/// <param name="indexPosition">座標インデックス</param>
	/// <param name="indexVertex">頂点インデックス</param>
	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	/// <summary>
	/// 平滑化された頂点法線の計算
	/// </summary>
	void CalculateSmoothedVertexNormals();

public:
	//virtual void ModelInitialize();

	virtual const std::vector<VertexPosNormalUv> GetVertices();

	//virtual void Initialize() = 0;
};
#pragma endregion


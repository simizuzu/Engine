#pragma once
#pragma warning(push)
#include <array>
#include <vector>
#include <string>
#pragma warning(pop)

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

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

class FbxModel
{
public:
	bool isAnimetion;
	char pad1[7];

	//モデル名
	std::string name;
	//ノード配列
	std::vector<ModelMesh> meshes;
};
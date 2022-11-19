#pragma once
#include <string>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

struct VertexPosNormalUv
{
	Mathematics::Vector3 pos;		// xyz座標
	Mathematics::Vector3 normal;	// 法線ベクトル
	Mathematics::Vector2 uv;		// uv座標
};

struct ConstBufferData
{
	Mathematics::Vector4 color;	// 色
	Mathematics::Matrix4 mat;	// 3D変換行列
};


class Model
{
public: // 静的メンバ関数
	// OBJファイルから3Dモデルを読み込む
	static Model* LoadFromOBJ();

private: // メンバ変数
	// 名前
	std::string name;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;

public: // メンバ関数
	void Initialize(const std::string& filePath);

public:
	void LoadMaterial(const std::string& directoryPath, const std::string& filePath);
};


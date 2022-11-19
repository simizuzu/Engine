#include "Model.h"
#include <Windows.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <cassert>
#include <fstream>
#include <sstream>

#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

Model* Model::LoadFromOBJ()
{
	Model* model_ = new Model();

	


	return model_;
}

void Model::Initialize(const std::string& filePath)
{
	const std::string filename = filePath + ".obj";
	const std::string directoryPath = filePath + "/";

	// ファイルストリーム
	std::ifstream file;
	// .objファイルを開く
	file.open(directoryPath + filename);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// 頂点座標
	std::vector<Mathematics::Vector3> positions;
	// 法線ベクトル
	std::vector<Mathematics::Vector3> normals;
	// テクスチャUV
	std::vector<Mathematics::Vector2> texcoords;

	// 1行ずつ読み込む
	std::string line;
	while (std::getline(file, line)) {
		// 1行分の文字列をストリームに変換する
		std::istringstream lineStream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		std::getline(lineStream, key, ' ');

		if (key == "mtllib")
		{
			// マテリアルのファイル読み込み
			std::string filename;
			lineStream >> filename;
			// マテリアル読み込み
		}
	}
}

void Model::LoadMaterial(const std::string& directoryPath, const std::string& filePath)
{
	// ファイルストリーム
	std::ifstream file;
	// マテリアルファイルを開く
}

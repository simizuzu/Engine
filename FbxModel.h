#pragma once

class FbxModel
{
public:
	bool isAnimetion;
	char pad1[7];

	//モデル名
	std::string name;
	//ノード配列
	std::vector<ModelMesh> meshes;

public:
	void LoadFromFBXInternal(const std::string& modelname);
};
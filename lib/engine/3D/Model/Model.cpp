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

	// �t�@�C���X�g���[��
	std::ifstream file;
	// .obj�t�@�C�����J��
	file.open(directoryPath + filename);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	// ���_���W
	std::vector<Mathematics::Vector3> positions;
	// �@���x�N�g��
	std::vector<Mathematics::Vector3> normals;
	// �e�N�X�`��UV
	std::vector<Mathematics::Vector2> texcoords;

	// 1�s���ǂݍ���
	std::string line;
	while (std::getline(file, line)) {
		// 1�s���̕�������X�g���[���ɕϊ�����
		std::istringstream lineStream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		std::getline(lineStream, key, ' ');

		if (key == "mtllib")
		{
			// �}�e���A���̃t�@�C���ǂݍ���
			std::string filename;
			lineStream >> filename;
			// �}�e���A���ǂݍ���
		}
	}
}

void Model::LoadMaterial(const std::string& directoryPath, const std::string& filePath)
{
	// �t�@�C���X�g���[��
	std::ifstream file;
	// �}�e���A���t�@�C�����J��
}

#pragma once
#include <string>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

struct VertexPosNormalUv
{
	Mathematics::Vector3 pos;		// xyz���W
	Mathematics::Vector3 normal;	// �@���x�N�g��
	Mathematics::Vector2 uv;		// uv���W
};

struct ConstBufferData
{
	Mathematics::Vector4 color;	// �F
	Mathematics::Matrix4 mat;	// 3D�ϊ��s��
};


class Model
{
public: // �ÓI�����o�֐�
	// OBJ�t�@�C������3D���f����ǂݍ���
	static Model* LoadFromOBJ();

private: // �����o�ϐ�
	// ���O
	std::string name;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

public: // �����o�֐�
	void Initialize(const std::string& filePath);

public:
	void LoadMaterial(const std::string& directoryPath, const std::string& filePath);
};


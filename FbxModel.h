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
	std::string name;				// �}�e���A����
	MyMath::Vector3 ambient;	// �A���r�G���g�e���x
	MyMath::Vector3 diffuse;	// �f�B�t���[�Y�e���x
	MyMath::Vector3 specular;	// �X�y�L�����[�e���x
	float alpha;					// �A���t�@
	std::string textureFilename;	// �e�N�X�`���t�@�C����
	float shininess = 1.0f;
	char pad[4];

	// �R���X�g���N�^
	Material() {
		ambient = { 0.3f,0.3f,0.3f };
		diffuse = { 0.0f,0.0f,0.0f };
		specular = { 0.0f,0.0f,0.0f };
		alpha = 1.0f;
	}
};

//�{�[���̍ő吔
constexpr int MAX_BONES = 128;
constexpr int MAX_BONE_INDICES = 4;

struct PosNormUvTangeColSkin
{
	MyMath::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // �ʒu���W
	MyMath::Vector3 normal; // �@��
	MyMath::Vector2 uv; // uv���W
	MyMath::Vector3 tangent; // �ڋ��
	MyMath::Vector4 color; // ���_�F

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// �{�[���̔ԍ�
	std::array<float, MAX_BONE_INDICES> boneWeight;	// �{�[���̏d��
};

struct PosNormUvTangeCol
{
	MyMath::Vector4 position = { 0.0f,0.f,0.0f,1.0f }; // �ʒu���W
	MyMath::Vector3 normal; // �@��
	MyMath::Vector2 uv; // uv���W
	MyMath::Vector3 tangent; // �ڋ��
	MyMath::Vector4 color; // ���_�F
};

struct PosNormSkin
{
	MyMath::Vector4 position; // �ʒu���W
	MyMath::Vector3 normal; // �@��

	std::array<UINT, MAX_BONE_INDICES> boneIndex;	// �{�[���̔ԍ�
	std::array<float, MAX_BONE_INDICES> boneWeight;	// �{�[���̏d��
};

struct PosNorm
{
	MyMath::Vector4 position; // �ʒu���W
	MyMath::Vector3 normal; // �@��
};
//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
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
	//���O
	std::string name;
	//���[�J���ό`�s��
	MyMath::Matrix4 transform;
	//�O���[�o���ό`�s��
	MyMath::Matrix4 globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
	//�q�m�[�h
	std::vector<Node>childrens;
};

struct Bone
{
public:
	//���O
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
	//�{�[���f�[�^
	std::array<MyMath::Matrix4, MAX_BONES> boneMat;
};

class ModelMesh
{
public:

	//���O
	std::string name;

	//���O
	std::string nodeName;

	//���_�f�[�^�̔z��
	std::vector<PosNormUvTangeColSkin> vertices;

	//�C���f�b�N�X�̔z��
	std::vector<uint32_t> indices;

	//�e�N�X�`��
	std::vector <std::string> textures;

	//�e�N�X�`��
	std::vector <std::string> texturesNormal;

	std::vector<Bone> vecBones;

	std::vector<MyMath::Matrix4> deformationMat;

	//�L��
	bool enable = false;
	char PADING[3]{};

	// �J���[
	float col[4] = { 1.0f,1.0f,1.0f,1.0f };
	char PADING1[4]{};

	// �}�e���A��
	Material material;

	Node* node = nullptr;

	//�`�撸�_�f�[�^
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

	//���f����
	std::string name;
	//�m�[�h�z��
	std::vector<ModelMesh> meshes;
};
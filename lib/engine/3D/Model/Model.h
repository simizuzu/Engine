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

#pragma region FBX
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

class fbxModel
{
public:
	bool isAnimetion;
	char pad1[7];

	//���f����
	std::string name;
	//�m�[�h�z��
	std::vector<ModelMesh> meshes;
};
#pragma endregion 

#pragma region OBJ

/// <summary>
/// 3D���f��
/// </summary>
class Model
{
public:
	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		MyMath::Vector3 ambient;	// �A���r�G���g�W��
		float pad1;						// �p�f�B���O
		MyMath::Vector3 diffuse;	// �f�B�t���[�Y�W��
		float pad2;						// �p�f�B���O
		MyMath::Vector3 specular;	// �X�y�L�����[�W��
		float alpha;					// �A���t�@
	};

public:
	/// <summary>
	/// OBJ�t�@�C������3D���f����ǂݍ���
	/// </summary>
	/// <returns>���f��</returns>
	static Model* LoadFromObj(const std::string& modelname, bool smoothing = false);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	/// <param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	static void SetDevice(ID3D12Device* device) { Model::device = device; };

private: // �ÓI�����o�ϐ�
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// �e�N�X�`���o�b�t�@
	 Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	D3D12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
		// �V�F�[�_���\�[�X�r���[�̃n���h��(GPU)
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@�r���[
	 D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	 D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	 std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	 std::vector<unsigned short> indices;
	// �}�e���A��
	 Material material;

private: // �����o�ϐ�
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	// �萔�o�b�t�@�i�}�e���A���j
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffB1;
	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@�̐���
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �e�N�X�`���f�[�^
	TextureData textureData;

	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;

private:
	/// <summary>
	/// OBJ�t�@�C������3D���f����ǂݍ���
	/// </summary>
	void LoadFromOBJInternal(const std::string& modelname, bool smoothing);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �e��o�b�t�@����
	/// </summary>
	void CreateBuffers();

	/// <summary>
	/// ���_�f�[�^�S�̂̃T�C�Y
	/// </summary>
	void CreateVBSize();

	/// <summary>
	/// �C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	/// </summary>
	void CreateIBSize();

	/// <summary>
	/// ���_�f�[�^�̐����擾
	/// </summary>
	/// <returns>���_�f�[�^�̎擾</returns>
	inline size_t GetVertexCount();

	/// <summary>
	/// �G�b�W�������f�[�^�̒ǉ�
	/// </summary>
	/// <param name="indexPosition">���W�C���f�b�N�X</param>
	/// <param name="indexVertex">���_�C���f�b�N�X</param>
	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	/// <summary>
	/// ���������ꂽ���_�@���̌v�Z
	/// </summary>
	void CalculateSmoothedVertexNormals();

public:
	//virtual void ModelInitialize();

	virtual const std::vector<VertexPosNormalUv> GetVertices();

	//virtual void Initialize() = 0;
};
#pragma endregion


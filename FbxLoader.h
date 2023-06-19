#pragma once

#include <d3d12.h>
#include <wrl.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/cimport.h>

#include "ObjModel.h"

class FbxLoader
{
private:
	//�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device_;

	std::string directoryPath;
	const aiScene* mScene;

	bool anicmatrixion = false;
	char pad1[7] = {};

	bool inverseU = false;
	bool inverseV = false;
	char pad2[6] = {};

	const size_t MAX_BONE_INDICES = 4;

	//�ǂݍ��݂̃f�t�H���g�t���O
	const UINT ASSIMP_LOAD_FLAG_DEFAULT =
		aiProcess_Triangulate | //�O�p�ʉ�
		aiProcess_CalcTangentSpace | //�ڐ��x�N�g������
		aiProcess_GenSmoothNormals | //�X���[�W���O�x�N�g������
		aiProcess_GenUVCoords | //��}�b�s���O��K�؂�UV���W�ɕϊ�
		aiProcess_RemoveRedundantMaterials | //�璷�ȃ}�e���A�����폜
		aiProcess_OptimizeMeshes | //���b�V�������œK��
		aiProcess_JoinIdenticalVertices |//�C���f�b�N�X�𐶐�
		aiProcess_LimitBoneWeights |//�e���_���e�����󂯂�{�[����4�ɐ���
		aiProcess_ConvertToLeftHanded;//����n��
	char pad3[4] = {};

public:
	static FbxLoader* GetInstance();
	
	void Initailize(ID3D12Device* device);

	void Finalize();

	//void LoadModel(FbxModel* model, const std::string& modelDirectory,bool inverseU_, bool inverseV_);
};

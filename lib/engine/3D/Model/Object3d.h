#pragma once
#include <d3d12.h>
#include <memory>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"
#include "Shader.h"
#include "WorldTransform.h"

#include "Matrix4.h"

class Object3d
{
private: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device, int width, int height);

	static void CreateGraphicsPipeline();

	static Object3d* Create();

private:
	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// �R�}���h���X�g
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	// �p�C�v���C���X�e�[�g
	static RootsigSetPip pip;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	//void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(WorldTransform* worldTransform);

	// setter
	void SetModel(Model* model);

private:
	// ���f��
	Model* model = nullptr;
	// ���[���h�g�����X�t�H�[��
	WorldTransform* worldTransform_ = nullptr;
};
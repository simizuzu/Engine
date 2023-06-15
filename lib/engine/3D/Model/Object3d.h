#pragma once
#include <d3d12.h>
#include <memory>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"
#include "Shader.h"
#include "Light.h"

#include "Camera.h"
#include "Matrix4.h"

class Object3d
{
public:
	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		//Mathematics::Matrix4 mat;	// 3D�ϊ��s��
		MyMath::Matrix4 viewproj;
		MyMath::Matrix4 world;
		MyMath::Vector3 cameraPos;
	};

public: // �ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device, int width, int height);

	static void CreateGraphicsPipeline();

	static Object3d* Create();

	static void SetLight(Light*light);

private:
	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// �R�}���h���X�g
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	// �p�C�v���C���X�e�[�g
	static RootsigSetPip pip;
	//���C�g
	static Light* light;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	// setter
	void SetModel(Model* model);
	void SetPosition(MyMath::Vector3 position_);
	void SetScale(MyMath::Vector3 scale_);
	void SetRotation(MyMath::Vector3 rotation_);

public:
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr <ID3D12Resource> constBuffB0;
	// �F
	MyMath::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	// ���[�J���X�P�[��
	MyMath::Vector3 scale = { 1.0f,1.0f,1.0f };
	// X,Y,Z�����̃��[�J����]�p
	MyMath::Vector3 rotation = { 0.0f,0.0f,0.0f };
	// ���[�J�����W
	MyMath::Vector3 position = { 0.0f,0.0f,0.0f };
	// ���[���h�ϊ��s��
	MyMath::Matrix4 matWorld;
	// �e�I�u�W�F�N�g
	Object3d* parent = nullptr;
	// ���f��
	Model* model = nullptr;
};

namespace MyMath
{
	Vector3 GetWorldPosition(Object3d& transform);
	Matrix4 MakeWorldMatrix4(Object3d& transform);
}
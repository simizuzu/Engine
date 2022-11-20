#pragma once
#include <d3d12.h>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"

#include "Matrix4.h"

class Object3d
{
public:
	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		Mathematics::Matrix4 mat;	// 3D�ϊ��s��
	};

public: // �ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device, int width, int height);

	static void CreateGraphicsPipeline();

	static Object3d* Create();

private:// �ÓI�����o�֐�(����J)
	static void UpdateViewMatrix();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// �R�}���h���X�g
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	

	// �N���X�Ăяo��
	static Pipeline* pipeline;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


};
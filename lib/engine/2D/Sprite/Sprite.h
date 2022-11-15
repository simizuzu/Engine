#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>

#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

class Sprite
{
public:
	// ���_�ԍ�
	enum VertexNumber {
		LB,	// ����
		LT,	// ����
		RB,	// �E��
		RT,	// �E��
	};

//public: 
//	/// <summary>
//	/// ���_�f�[�^�\����
//	/// </summary>
//	struct VertexPosUv
//	{
//		Mathematics::Vector3 pos;
//		Mathematics::Vector2 uv;
//	};
//
//	struct ConstBufferData
//	{
//		Mathematics::Vector4 color;
//		Mathematics::Matrix4 mat;
//	};

public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device_;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorSize_;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* commandList_;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature_;
	// �v���W�F�N�V�����s��
	static Mathematics::Matrix4 matProjection_;
	// �p�C�v���C���X�e�[�g
	static std::array<RootsigSetPip, 6> pipelineState;
	// ���_�V�F�[�_�I�u�W�F�N�g
	static ComPtr<ID3DBlob> vsBlob;
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	static ComPtr<ID3DBlob> psBlob;

private: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �G���[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	// �C���v�b�g���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout{};
	// ���W
	Mathematics::Vector2 position_ = { 0.0f,0.0f };
	// �F
	Mathematics::Vector4 color_ = { 1, 1, 1, 1 };
	// �p�x
	float rotation_ = 0.0f;
	// �\���T�C�Y(�P�ʂ�pixel)
	Mathematics::Vector2 size_ = { 100.0f,100.0f };
	// �e�N�X�`���ԍ�
	uint32_t textureIndex_ = 0;
	// �u�����h���[�h
	int blendMode = (int)BlendMode::Alpha;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���_�o�b�t�@�֘A�̏�����
	/// </summary>
	void InitializeVertexBuff();

public: // �ÓI�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �`��O����
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

public: // setter,getter
	/// <summary>
	/// ���W���Z�b�g
	/// </summary>
	/// <param name="position">: ���W{ x,y }</param>
	void SetPosiotion(const Mathematics::Vector2& position) { position_ = position; }

	/// <summary>
	/// ��]�p���Z�b�g
	/// </summary>
	/// <param name="rotation">: �p�x</param>
	void SetRotation(float rotation) { rotation_ = rotation; }

	/// <summary>
	/// �X�v���C�g�̑傫�����Z�b�g
	/// </summary>
	/// <param name="rotation">�T�C�Y</param>
	void SetSize(const Mathematics::Vector2& size) { size_ = size; }

	/// <summary>
	/// �X�v���C�g�̐F���Z�b�g
	/// </summary>
	/// <param name="color">: �F{ red,blue,green,alpha }</param>
	void SetColor(const Mathematics::Vector4& color) { color_ = color; }

	/// <summary>
	/// �e�N�X�`���ԍ����Z�b�g
	/// </summary>
	/// <param name="textureIndex">: �e�N�X�`���ԍ�</param>
	void SetTextureIndex(uint32_t textureIndex) { textureIndex_ = textureIndex; }

	/// <summary>
	/// �u�����h��ݒ�
	/// </summary>
	void SetBlendMode(BlendMode);

	// ���W
	const Mathematics::Vector2& GetPosition() const { return position_; }
	// �p�x
	float GetRotation() const { return rotation_; }
	// �F
	const Mathematics::Vector4& GetColor() const { return color_; }
	// �T�C�Y
	const Mathematics::Vector2& GetSize() const { return size_; }
	// �e�N�X�`���ԍ�
	uint32_t GetTextureIndex() { return textureIndex_; }

private: // �N���X�Ăяo��
	TextureManager* textureManager_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	static Shader* shader_;
	static Pipeline* pipeline_;
	static WinApp* winApp_;
};
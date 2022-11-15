#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>

#include "TextureManager.h"
#include "DirectXCommon.h"
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

	enum class BlendMode
	{
		None,	// �u�����h����
		Alpha,	// �A���t�@
		Add,	// ���Z
		Sub,	// ���Z
		Mul,	// ��Z
		Inv,	// �F���]

		CountOfBlendMode, // �ő�u�����h���[�h��
	};

public: 
	
	/// <summary>
	/// ���_�f�[�^�\����
	/// </summary>
	struct VertexPosUv
	{
		Mathematics::Vector3 pos;
		Mathematics::Vector2 uv;
	};

	struct ConstBufferData
	{
		Mathematics::Vector4 color;
		Mathematics::Matrix4 mat;
	};

public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> vsBlob;
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;
	// �G���[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob;
	// �p�C�v���C���X�e�[�g
	ComPtr<ID3D12PipelineState> pipelineState;

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

	/// <summary>
	/// �V�F�[�_�̓ǂݍ��݊֘A�̏�����
	/// </summary>
	void InitializeShadeLoad();

public:
	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList, BlendMode blendMode = BlendMode::None);

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

#pragma region pipeline�N���X�p
	// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> GetVsBlob() { return vsBlob; }
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> GetPsBlob() { return psBlob; }
	// �G���[�I�u�W�F�N�g
	ComPtr<ID3DBlob> GetErrorBlob() { return errorBlob; }

#pragma endregion

private: // �N���X�Ăяo��
	TextureManager* textureManager_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Shader* shader_ = nullptr;
	Pipeline* pipeline_ = nullptr;
};
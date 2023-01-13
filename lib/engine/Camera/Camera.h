#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "DirectX12Math.h"

struct ConstBufferDataViewProjection
{
	// ���[���h�s��
	Mathematics::Matrix4 world;
	// ���[���h���W
	Mathematics::Matrix4 matWorld;

	// ���[���h �� �r���[�ϊ��s��
	Mathematics::Matrix4 view;
	// �r���[ �� �v���W�F�N�V�����ϊ��s��
	Mathematics::Matrix4 projection;
	// �J�������W�i���[���h���W�j
	Mathematics::Vector3 cameraPos;
};

struct ViewProjection
{
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataViewProjection* constBuffMap = nullptr;
};

class Camera
{
public:
#pragma region �r���[�s��ݒ�
	// ���_���W
	Mathematics::Vector3 eye_;
	// �����_���W
	Mathematics::Vector3 target_;
	// ������x�N�g��
	Mathematics::Vector3 up_;
#pragma endregion

private:
#pragma region �ˉe�s��ݒ�
	// �J������p
	float fovAngleY = MyMathUtility::degree2Radius * 45.0f;
	// ��O
	float nearZ_ = 0.1f;
	// ���s��
	float farZ_ = 1000.0f;
	// �A�X�y�N�g��(��ʉ���/��ʏc��)
	float aspect = 0.0f;
#pragma endregion
	// �r���[�s��
	Mathematics::Matrix4 matView_;
	// �r���[�t�s��
	Mathematics::Matrix4 matViewInverse_;
	// �ˉe�s��
	Mathematics::Matrix4 matProjection_;;
	// �J��������
	float distance = 50.0f;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �萔�o�b�t�@����
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// �}�b�s���O
	/// </summary>
	void Map();
	/// <summary>
	/// �r���[�s��̍X�V
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// �r���[�s��̓]��
	/// </summary>
	void TransferMatrix();

public:
	const Mathematics::Matrix4& GetMatView();
	const Mathematics::Matrix4& GetMatViewInverse();
	const Mathematics::Matrix4& GetMatProjection();

	const Mathematics::Vector3& GetEye();
	const Mathematics::Vector3& GetTarget();
	const Mathematics::Vector3& GetUp();

	void SetEye(const Mathematics::Vector3& eye);
	void SetTarget(const Mathematics::Vector3& target);
	void SetUp(const Mathematics::Vector3& up);
	void SetFarZ(const float& farZ);
	void SetNearZ(const float& nearZ);
};
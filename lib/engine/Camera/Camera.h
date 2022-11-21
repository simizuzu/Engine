#pragma once
#include "DirectX12Math.h"

struct ConstBufferDataViewProjection
{
	Mathematics::Matrix4 view;       // ���[���h �� �r���[�ϊ��s��
	Mathematics::Matrix4 projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
	Mathematics::Vector3 cameraPos;  // �J�������W�i���[���h���W�j
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
private:
#pragma region �r���[�s��ݒ�
	// ���_���W
	Mathematics::Vector3 eye_ = { 0.0f, 0.0f, -100.0f };
	// �����_���W
	Mathematics::Vector3 target_ = { 0, 0, 0 };
	// ������x�N�g��
	Mathematics::Vector3 up_ = { 0, 1, 0 };
#pragma endregion

#pragma region �ˉe�s��ݒ�
	// �J������p
	float fovAngleY = 0.0f;
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
	const Mathematics::Matrix4& GetMatView() { return matView_; }
	const Mathematics::Matrix4& GetMatViewInverse() { return matViewInverse_; }
	const Mathematics::Matrix4& GetMatProjection() { return matProjection_; }

	const Mathematics::Vector3& GetEye() { return eye_; }
	const Mathematics::Vector3& GetTarget() { return target_; }
	const Mathematics::Vector3& GetUp() { return up_; }

	void SetEye(const Mathematics::Vector3& eye) { eye_ = eye; }
	void SetTarget(const Mathematics::Vector3& target) { target_ = target; }
	void SetUp(const Mathematics::Vector3& up) { up_ = up; }
	void SetFarZ(const float& farZ) { farZ_ = farZ; }
	void SetNearZ(const float& nearZ) { nearZ_ = nearZ; }
};
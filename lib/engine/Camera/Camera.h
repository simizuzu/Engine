#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "DirectX12Math.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "EngineUtility.h"

class Camera
{
public:
#pragma region �r���[�s��ݒ�
	// ���_���W
	MyMath::Vector3 eye_;
	// �����_���W
	MyMath::Vector3 target_;
	// ������x�N�g��
	MyMath::Vector3 up_;
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
	MyMath::Matrix4 matView_;
	// �r���[�t�s��
	MyMath::Matrix4 matViewInverse_;
	// �ˉe�s��
	MyMath::Matrix4 matProjection_;;
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
	const MyMath::Matrix4& GetMatView();
	const MyMath::Matrix4& GetMatViewInverse();
	const MyMath::Matrix4& GetMatProjection();

	const MyMath::Vector3& GetEye();
	const MyMath::Vector3& GetTarget();
	const MyMath::Vector3& GetUp();

	void SetEye(const MyMath::Vector3& eye);
	void SetTarget(const MyMath::Vector3& target);
	void SetUp(const MyMath::Vector3& up);
	void SetFarZ(const float& farZ);
	void SetNearZ(const float& nearZ);
};
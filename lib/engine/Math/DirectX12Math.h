#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "WorldTransform.h"

namespace MyMathUtility
{
	// �x���烉�W�A���ɕϊ�����萔
	const float PI = 3.141592654f;
	constexpr float degree2Radius = 3.1415926535897931f / 180.0f;
	constexpr float PIHalf = 3.1415926535897931f / 2.0f;

	// ���������߂�(2����)
	float Vector2Length(const Mathematics::Vector2& v);
	// ���������߂�(3����)
	float Vector3Length(const Mathematics::Vector3& v);

	// ���K������
	Mathematics::Vector3 MakeNormalize(Mathematics::Vector3 v);

	// �P�ʍs������߂�
	Mathematics::Matrix4 MakeIdentity();
	// �g��k�������߂�
	Mathematics::Matrix4 MakeScaling(Mathematics::Vector3 scale);
	// ��]�s������߂�
	Mathematics::Matrix4 MakeRotation(Mathematics::Vector3 rot);
	// ���s�ړ��s������߂�
	Mathematics::Matrix4 MakeTranslation(Mathematics::Vector3 trans);
	// ���[���h�s��̌v�Z
	Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	/// <summary>
	/// 1���̃��[���h�g�����X�t�H�[���X�V�֐�
	/// </summary>
	/// <param name="childWorldtrans">�q��worldTransform</param>
	void WorldTransUpdate(WorldTransform& childWorldtrans);

	// �x�N�g���ƍs��̊|���Z
	Mathematics::Matrix4 MatMulVector(Mathematics::Matrix4 m, Mathematics::Vector3 v);

	// ���s���e�ϊ�(����n)
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);
	// ���s���e�ϊ�(����n)
	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);

	// �r���[�s��̍쐬
	Mathematics::Matrix4 MakeLookAtLH( Mathematics::Vector3& eye,  Mathematics::Vector3& target, Mathematics::Vector3& up);
	// �������e�쐬
	Mathematics::Matrix4 MakePerspective(float fogAngleY, float aspectRatio, float nearZ, float farZ);
	// �t�s��
	Mathematics::Matrix4 MakeInverse(Mathematics::Matrix4& mat);

	// ���`���
	float Lerp(float a, float b, float t);

} // namespace MyMathUtility
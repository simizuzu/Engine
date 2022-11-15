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
	Mathematics::Matrix4 MakeScaling(Mathematics::Matrix4 m, Mathematics::Vector3 scale);
	// ��]�s������߂�
	Mathematics::Matrix4 MakeRotationZ(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotationX(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotationY(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotation(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	// ���s�ړ��s������߂�
	Mathematics::Matrix4 MakeTranslation(Mathematics::Matrix4 m, Mathematics::Vector3 trans);
	// ���[���h�s��̌v�Z
	Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);
	// �x�N�g���ƍs��̊|���Z
	Mathematics::Matrix4 MatMulVector(Mathematics::Matrix4 m, Mathematics::Vector3 v);

	Mathematics::Matrix4 MakeOrthographic(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);

	// ���`���
	float Lerp(float a, float b, float t);

} // namespace MyMathUtility
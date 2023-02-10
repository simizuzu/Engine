#pragma once
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace MyMathUtility
{
	// �x���烉�W�A���ɕϊ�����萔
	const float PI = 3.141592654f;
	constexpr float degree2Radius = 3.1415926535897931f / 180.0f;
	constexpr float PIHalf = 3.1415926535897931f / 2.0f;

	//��(�C�v�V����)
	constexpr float EPSILON = 2.2204460492503131E-16f;

	// ���������߂�(2����)
	float Vector2Length(const Mathematics::Vector2& v);
	// ���������߂�(3����)
	float Vector3Length(const Mathematics::Vector3& v);

	// ���K������
	Mathematics::Vector3 MakeNormalize(Mathematics::Vector3 v);

	// �P�ʍs������߂�
	Mathematics::Matrix4 MakeIdentity();
	// �g��k�������߂�
	Mathematics::Matrix4 MakeScaling(const Mathematics::Vector3& scale);
	// ��]�s������߂�
	Mathematics::Matrix4 MakeRotation(const Mathematics::Vector3& rot);
	// ���s�ړ��s������߂�
	Mathematics::Matrix4 MakeTranslation(const Mathematics::Vector3& trans);
	//// ���[���h�s��̌v�Z
	//Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	///// <summary>
	///// 1���̃��[���h�g�����X�t�H�[���X�V�֐�
	///// </summary>
	///// <param name="childWorldtrans">�q��worldTransform</param>
	//void WorldTransUpdate(WorldTransform& childWorldtrans);

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

	Mathematics::Vector3 Dot(const Mathematics::Vector3& a, const Mathematics::Vector3 b);

	// �l�����������m�F����
	bool Approximately(float a, float b);

	// ���`���
	float Lerp(float a, float b, float t);
	Mathematics::Vector3 Lerp(Mathematics::Vector3 a, Mathematics::Vector3 b, float t);

	/// <summary>
	/// �G���~�[�g�Ȑ�
	/// </summary>
	/// <param name="p0">����_</param>
	/// <param name="p1">����_</param>
	/// <param name="v0">����_</param>
	/// <param name="v1">����_</param>
	/// <param name="t">����(0.0�`1.0)</param>
	/// <returns></returns>
	Mathematics::Vector3 HermiteGetPoint(Mathematics::Vector3 p0, Mathematics::Vector3 p1, Mathematics::Vector3 v0, Mathematics::Vector3 v1, float t);

	// Sin,Cos,Tan�֐�
	float Sin(float sin);
	float Cos(float cos);
	float Tan(float tan);

	float Asin(float sin);
	float Acos(float cos);
	float Atan(float tan);
	float Atan2(float y, float x);

	void Complement(float& x1, float x2, float flame);

	float Clamp(float Value, const float low, const float high);
	float Clamp0To1(float val);

} // namespace MyMathUtility

namespace Mathematics
{
	// �x�N�g���ƍs��̊|���Z
	Vector3 Vec3Mat4Mul(Vector3& vec, Matrix4& mat);

	// �L���b�g�����[�����X�v���C���Ȑ�
	Vector3 CatMullRomSpline(std::vector<Vector3>& points, float t);

	/// �������ɓ��e���ꂽ���������瓊�e���������Z�o
	float LenSegLineOfSeparateAxis(Vector3* sep, Vector3* e1, Vector3* e2, Vector3* e3 = 0);
}
#pragma once
#include"vector3.h"
#include"Matrix4.h"

namespace MyMath
{
	class Quaternion
	{
	public:
		float x_;
		float y_;
		float z_;
		float w_;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const aiQuaternion& q);

		//Quaternion�̐�
		Quaternion Multiply(Quaternion r);
		//�P��Quaternion��Ԃ�
		Quaternion IdentityQuaternion();
		//����Quaternion��Ԃ�
		Quaternion Conjugate();
		//Quaternion��norm��Ԃ�
		float Norm() const;
		//���K������Quaternion��Ԃ�
		Quaternion Normalize();
		//�tQuaternion��Ԃ�
		Quaternion INverse();
		//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
		MyMath::Vector3 RotateVector(const MyMath::Vector3& vector);
		//Quaternion�����]�s������߂�
		MyMath::Matrix4 MakeRotateMatrix();
		//�C�ӎ���]��\��Quaternion�̐���
		Quaternion MakeAxisAngle(const MyMath::Vector3& axsi, float angle);
		// u����v�ւ̉�]�𐶐�
		Quaternion DirectionToDirection(const MyMath::Vector3& u, const MyMath::Vector3& v);

		//���ʐ��`���
		Quaternion Slerp(const Quaternion& p, float t);
		float Dot(const Quaternion& q)const;


		//�P�����Z�q�I�[�o�[���[�h
		Quaternion operator + ();
		Quaternion operator - ()const;

		//������Z�q�I�[�o�[���[�h
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (float s);
		Quaternion& operator /= (float s);
		Quaternion& operator *= (const Quaternion& q);
	};

	//2�����Z�q�I�[�o�[���[�h
	const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q, float s);
	const Quaternion operator * (float s, const Quaternion& q);
	const Quaternion operator / (const Quaternion& q, float s);
	const MyMath::Vector3 operator*(Quaternion q, MyMath::Vector3 vec);
}
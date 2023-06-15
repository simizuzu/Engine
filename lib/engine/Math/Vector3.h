#pragma once
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/cimport.h>

namespace MyMath
{
	/// <summary>
	/// 3�����x�N�g��
	/// </summary>
	class Vector3
	{
	public:
		float x;//x����
		float y;//y����
		float z;//z����

	public:
		//�R���X�g���N�g
		Vector3();                //�[���x�N�g���Ƃ��Đ���
		Vector3(float x, float y, float z);//x����,y�������w�肵�Ă̐���
		Vector3(const aiVector3D& mat);//Assimp�pVector3

		//�@�����o�֐�
		float length() const;              //�m����(����)�����߂�
		Vector3& normalize();              //���K������
		Vector3 Norm()const;
		float dot(const Vector3& v)const;  //���ς����߂�
		Vector3 cross(const Vector3& v)const; //�O�ς����߂�

		//�P�����Z�q�I�[�o�[���[�h
		Vector3 operator+() const;
		Vector3 operator-() const;

		//������Z�q�I�[�o�[���[�h
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
	};

	//2�����Z�q�I�|�o�[���[�h
	//�������Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽�߂ɁA�ȉ��̂悤�ɏ������Ă���
	const Vector3 operator+(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v1, const Vector3& v2);
	const Vector3 operator*(const Vector3& v, float s);
	const Vector3 operator*(float s, const Vector3& v);
	const Vector3 operator/(const Vector3& v, float s);
}
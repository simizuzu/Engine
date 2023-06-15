#pragma once

#include <cmath>
#include <array>
#include "Vector3.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/cimport.h>

namespace MyMath
{
	class Matrix4
	{
	public:
		std::array<std::array<float, 4>, 4>m;

		// �R���X�g���N�^
		Matrix4();

		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		//Assimp�pMatrix4
		Matrix4(const aiMatrix4x4& mat);
		Matrix4 Transpose();

		Matrix4 identity();

		/// <summary>
		/// ������Z�q
		/// </summary>
		Matrix4& operator=(const Matrix4& _m);

		// ���Z
		Matrix4& operator+=(const Matrix4& mat);
		// ���Z
		Matrix4& operator-=(const Matrix4& mat);
		// ��Z
		Matrix4& operator*=(const Matrix4& mat);
		// ���Z
		Matrix4 operator+(const Matrix4& mat) const;
		// ���Z
		Matrix4 operator-(const Matrix4& mat) const;
		// ��Z
		Matrix4 operator*(const Matrix4& mat) const;
	};
}



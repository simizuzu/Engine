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

		// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
		Matrix4();

		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		//Assimp—pMatrix4
		Matrix4(const aiMatrix4x4& mat);
		Matrix4 Transpose();

		Matrix4 identity();

		/// <summary>
		/// ‘ã“ü‰‰Zq
		/// </summary>
		Matrix4& operator=(const Matrix4& _m);

		// ‰ÁZ
		Matrix4& operator+=(const Matrix4& mat);
		// Œ¸Z
		Matrix4& operator-=(const Matrix4& mat);
		// æZ
		Matrix4& operator*=(const Matrix4& mat);
		// ‰ÁZ
		Matrix4 operator+(const Matrix4& mat) const;
		// Œ¸Z
		Matrix4 operator-(const Matrix4& mat) const;
		// æZ
		Matrix4 operator*(const Matrix4& mat) const;
	};
}



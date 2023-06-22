#include "Matrix4.h"

namespace MyMath
{
	Matrix4::Matrix4()
	{
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;
		m[1][3] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
		m[2][3] = 0.0f;

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	Matrix4::Matrix4(
		float m00, float m01, float m02, float m03, 
		float m10, float m11, float m12, float m13, 
		float m20, float m21, float m22, float m23, 
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}

	Matrix4::Matrix4(const aiMatrix4x4& mat)
	{
		m[0][0] = mat.a1;
		m[0][1] = mat.a2;
		m[0][2] = mat.a3;
		m[0][3] = mat.a4;

		m[1][0] = mat.b1;
		m[1][1] = mat.b2;
		m[1][2] = mat.b3;
		m[1][3] = mat.b4;

		m[2][0] = mat.c1;
		m[2][1] = mat.c2;
		m[2][2] = mat.c3;
		m[2][3] = mat.c4;

		m[3][0] = mat.d1;
		m[3][1] = mat.d2;
		m[3][2] = mat.d3;
		m[3][3] = mat.d4;
	}

	Matrix4 Matrix4::Transpose()
	{
		MyMath::Matrix4 tmp(*this);
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = i; j < 4; j++)
			{
				float f = tmp.m[i][j];
				tmp.m[i][j] = tmp.m[j][i];
				tmp.m[j][i] = f;
			}
		}

		return tmp;
	}

	// 単位行列を求める
	Matrix4 Matrix4::identity()
	{
		static const Matrix4 result
		{
			1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
		};

		return result;
	}

	Matrix4& Matrix4::operator=(const Matrix4& _m)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = _m.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] += mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] -= mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& mat)
	{
		Matrix4 temp(*this);

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				double f = 0.0;
				for (size_t k = 0; k < 4; k++)
				{
					f += (double)temp.m[i][k] * (double)mat.m[k][j];

					m[i][j] = (float)f;
				}


			}
		}
		return *this;
	}

	Matrix4 Matrix4::operator+(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp += mat;
		return temp;
	}

	Matrix4 Matrix4::operator-(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp -= mat;
		return temp;
	}

	Matrix4 Matrix4::operator*(const Matrix4& mat) const
	{
		Matrix4 temp(*this);
		temp *= mat;
		return temp;
	}
}
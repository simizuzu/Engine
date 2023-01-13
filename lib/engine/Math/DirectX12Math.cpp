#include "DirectX12Math.h"
#include <cmath>
#include <cassert>

using namespace Mathematics;

namespace MyMathUtility
{
	float Vector2Length(const Vector2& v)
	{
		return (float)std::sqrt(v.x * v.x + v.y * v.y);
	}

	float Vector3Length(const Vector3& v)
	{
		return (float)std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	Vector3 MakeNormalize(Vector3 v)
	{
		float len = Vector3Length(v);
		if (len != 0) {
			return v /= len;
		}
		return v;
	}

	Matrix4 MakeIdentity()
	{
		Matrix4 matIdentity;
		matIdentity.m[0][0] = 1.0f;
		matIdentity.m[1][1] = 1.0f;
		matIdentity.m[2][2] = 1.0f;
		matIdentity.m[3][3] = 1.0f;

		return matIdentity;
	}

	Matrix4 MakeScaling(const Vector3& scale)
	{
		Matrix4 matScale;
		matScale.m[0][0] = scale.x;
		matScale.m[1][1] = scale.y;
		matScale.m[2][2] = scale.z;
		matScale.m[3][3] = 1.0f;

		return matScale;
	}

	Matrix4 MakeRotation(const Vector3& rot)
	{
		Matrix4 matRotX;
		matRotX = MakeIdentity();
		matRotX.m[1][1] = cos(rot.x);
		matRotX.m[1][2] = sin(rot.x);
		matRotX.m[2][1] = -sin(rot.x);
		matRotX.m[2][2] = cos(rot.x);

		Matrix4 matRotY;
		matRotY = MakeIdentity();
		matRotY.m[0][0] = cos(rot.y);
		matRotY.m[0][2] = -sin(rot.y);
		matRotY.m[2][0] = sin(rot.y);
		matRotY.m[2][2] = cos(rot.y);

		Matrix4 matRotZ;
		matRotZ = MakeIdentity();
		matRotZ.m[0][0] = cos(rot.z);
		matRotZ.m[0][1] = sin(rot.z);
		matRotZ.m[1][0] = -sin(rot.z);
		matRotZ.m[1][1] = cos(rot.z);

		Matrix4 matRot;
		matRot = MakeIdentity();

		matRot *= matRotZ;
		matRot *= matRotX;
		matRot *= matRotY;
		return matRot;
	}

	Matrix4 MakeTranslation(const Vector3& trans)
	{
		Matrix4 matTrans;
		matTrans = MakeIdentity();
		matTrans.m[3][0] = trans.x;
		matTrans.m[3][1] = trans.y;
		matTrans.m[3][2] = trans.z;
		return matTrans;
	}

	//Matrix4 CreateMatrix(const WorldTransform& worldTransform)
	//{
	//	Matrix4 matWorld;

	//	matWorld = MakeIdentity();
	//	matWorld = MakeScaling(worldTransform.scale_);
	//	matWorld = MakeRotation(worldTransform.rotation_);
	//	matWorld = MakeTranslation(worldTransform.translation_);

	//	if (worldTransform.parent_ != nullptr)
	//	{
	//		matWorld *= worldTransform.parent_->matWorld_;
	//	}

	//	return matWorld;
	//}

	//void WorldTransUpdate(WorldTransform& childWorldtrans)
	//{
	//	childWorldtrans.matWorld_ = CreateMatrix(childWorldtrans);			// ���������s��̌v�Z
	//	childWorldtrans.matWorld_ *= childWorldtrans.parent_->matWorld_;	// parent_�̃��[���h�s��̊|���Z���
	//	childWorldtrans.TransferMatrix();									// �s��̓]��
	//}

	Matrix4 MatMulVector(Matrix4 m, Vector3 v)
	{
		return Matrix4();
	}

	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix)
	{
		float width = 1.0f / (right - left);
		float height = 1.0f / (top - bottom);
		float range = 1.0f / (far_ - near_);

		matrix.m[0][0] = width * 2;

		matrix.m[1][1] = height * 2;

		matrix.m[2][2] = range;

		matrix.m[3][0] = -(left + right) * width;
		matrix.m[3][1] = -(top + bottom) * height;
		matrix.m[3][2] = range * -near_;
		matrix.m[3][3] = 1.0f;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;
	}

	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Matrix4& matrix)
	{
		float width = 1.0f / (right - left);
		float height = 1.0f / (top - bottom);
		float range = 1.0f / (far_ - near_);

		matrix.m[0][0] = width * 2;

		matrix.m[1][1] = height * 2;

		matrix.m[2][2] = range;

		matrix.m[3][0] = -(left + right) * width;
		matrix.m[3][1] = -(top + bottom) * height;
		matrix.m[3][2] = range * -near_;
		matrix.m[3][3] = 1.0f;

		matrix.m[0][1] = matrix.m[0][2] = matrix.m[0][3] =
			matrix.m[1][0] = matrix.m[1][2] = matrix.m[1][3] =
			matrix.m[2][0] = matrix.m[2][1] = matrix.m[2][3] = 0.0f;

	}

	Matrix4 MakeLookAtLH(Vector3& eye, Vector3& target, Vector3& up)
	{
		Vector3 zVec = target - eye;
		zVec.normalize();

		Vector3 xVec = up.cross(zVec);
		xVec.normalize();

		Vector3 yVec = zVec.cross(xVec);
		yVec.normalize();

		Matrix4 matrix;
		matrix.m[0][0] = xVec.x;
		matrix.m[0][1] = xVec.y;
		matrix.m[0][2] = xVec.z;

		matrix.m[1][0] = yVec.x;
		matrix.m[1][1] = yVec.y;
		matrix.m[1][2] = yVec.z;

		matrix.m[2][0] = zVec.x;
		matrix.m[2][1] = zVec.y;
		matrix.m[2][2] = zVec.z;

		matrix.m[3][0] = -eye.x;
		matrix.m[3][1] = -eye.y;
		matrix.m[3][2] = -eye.z;

		return matrix;
	}

	Matrix4 MakePerspective(float fogAngleY, float aspectRatio, float nearZ, float farZ)
	{
		// �A�X�y�N�g����쐬

		float sinFov = std::sin(0.5f * fogAngleY);
		float cosFov = std::cos(0.5f * fogAngleY);

		float height = cosFov / sinFov;
		float width = height / aspectRatio;
		float range = farZ / (farZ - nearZ);

		Matrix4 matrix;
		matrix.m[0][0] = height / aspectRatio;
		matrix.m[1][1] = cosFov / sinFov;
		matrix.m[2][2] = range;
		matrix.m[2][3] = 1.0f;
		matrix.m[3][2] = -range * nearZ;

		matrix.m[0][1] = 0.0f;
		matrix.m[0][2] = 0.0f;
		matrix.m[0][3] = 0.0f;
		matrix.m[1][0] = 0.0f;
		matrix.m[1][2] = 0.0f;
		matrix.m[1][3] = 0.0f;
		matrix.m[2][0] = 0.0f;
		matrix.m[2][1] = 0.0f;
		matrix.m[3][0] = 0.0f;
		matrix.m[3][1] = 0.0f;
		matrix.m[3][3] = 0.0f;

		return matrix;
	}

	Matrix4 MakeInverse(Matrix4& mat)
	{
		//�|���o���@���s���s��
		float sweep[4][8]{};
		//�萔�{�p
		float constTimes = 0.0f;
		//���e����덷
		float MAX_ERR = 1e-10f;
		//�߂�l�p
		Matrix4 retMat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//weep�̍����ɋt�s������߂�s����Z�b�g
				sweep[i][j] = mat.m[i][j];

				//sweep�̉E���ɒP�ʍs����Z�b�g
				sweep[i][4 + j] = MakeIdentity().m[i][j];
			}
		}

		//�S�Ă̗�̑Ίp�����ɑ΂���J��Ԃ�
		for (int i = 0; i < 4; i++)
		{
			//�ő�̐�Βl�𒍖ڑΊp�����̐�Βl�Ɖ���
			float max = std::fabs(sweep[i][i]);
			int maxIndex = i;

			//i��ڂ��ő�̐�Βl�ƂȂ�s��T��
			for (int j = i + 1; j < 4; j++)
			{
				if (std::fabs(sweep[j][i]) > max)
				{
					max = std::fabs(sweep[j][i]);
					maxIndex = j;
				}
			}

			if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
			{
				//�t�s��͋��߂��Ȃ�
				return MakeIdentity();
			}

			//����(1):i�s�ڂ�maxIndex�s�ڂ����ւ���
			if (i != maxIndex)
			{
				for (int j = 0; j < 8; j++)
				{
					float tmp = sweep[maxIndex][j];
					sweep[maxIndex][j] = sweep[i][j];
					sweep[i][j] = tmp;
				}
			}

			//sweep[i][i]�Ɋ|�����1�ɂȂ�l�����߂�
			constTimes = 1 / sweep[i][i];

			//����(2):p�s�ڂ�a�{����
			for (int j = 0; j < 8; j++)
			{
				//����ɂ��sweep[i][i]��1�ɂȂ�
				sweep[i][j] *= constTimes;
			}

			//����(3)�ɂ��i�s�ڈȊO�̍s��i��ڂ�0�ɂ���
			for (int j = 0; j < 4; j++)
			{
				if (j == i)
				{
					//i�s�ڂ͂��̂܂�
					continue;
				}

				//i�s�ڂɊ|����l�����߂�
				constTimes = -sweep[j][i];

				for (int k = 0; k < 8; k++)
				{
					//j�s�ڂ�i�s�ڂ�a�{�����s�𑫂�
					//����ɂ��sweep[j][i]��0�ɂȂ�
					sweep[j][k] += sweep[i][k] * constTimes;
				}
			}
		}

		//sweep�̉E������mat�̋t�s��
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				retMat.m[i][j] = sweep[i][4 + j];
			}
		}

		return retMat;
	}

	// ��̒l���قړ�������
	bool Approximately(float a, float b)
	{
		float tmp = 1e-06f * std::max(fabs(a), fabs(b));

		float tmp2 = EPSILON * 8.0f;

		if (fabs(b - a) < std::max(tmp, tmp2))
		{
			return true;
		}

		return false;
	}

	float Sin(float sin)
	{
		return std::sinf(sin);
	}

	float Asin(float sin)
	{
		return std::asinf(sin);
	}

	float Cos(float cos)
	{
		return std::cosf(cos);
	}

	float Acos(float cos)
	{
		return std::acosf(cos);
	}

	float Tan(float tan)
	{
		return std::tanf(tan);
	}

	float Atan(float tan)
	{
		return std::atanf(tan);
	}

	float Atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}

	void Complement(float& x1, float x2, float flame)
	{
		//�������o��
		float distanceX = x2 - x1;
		//������flame�Ŋ������l
		float dividedDistanceX = distanceX / flame;

		//������flame�Ŋ������l�𑫂�
		x1 += dividedDistanceX;
	}

	float Clamp(float Value, const float low, const float high)
	{
		if (high < Value)
		{
			Value = high;
		}

		if (Value < low)
		{
			Value = low;
		}

		return Value;
	}

	float Clamp0To1(float val)
	{
		if (val < 0.0f)
		{
			return 0.0f;
		}
		if (val > 1.0f)
		{
			return 1.0f;
		}

		return val;
	}

	// ���`���(0�`1)
	float Lerp(float a, float b, float t)
	{
		return a + (b - a) * Clamp0To1(t);
	}

	Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		Vector3 tmp;
		tmp.x = a.x + (b.x - a.x) * Clamp0To1(t);
		tmp.y = a.y + (b.y - a.y) * Clamp0To1(t);
		tmp.z = a.z + (b.z - a.z) * Clamp0To1(t);
		return tmp;
	}

	Vector3 HermiteGetPoint(Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t)
	{
		Vector3 c0 = 2.0f * p0 + -2.0f * p1 + v0 + v1;
		Vector3 c1 = -3.0f * p0 + 3.0f * p1 + -2.0f * v0 - v1;
		Vector3 c2 = v0;
		Vector3 c3 = p0;

		float t2 = t * t;
		float t3 = t2 * t;
		return c0 * t3 + c1 * t2 + c2 * t + c3;
	}

	float LenSegLineOfSeparateAxis(Vector3* sep, Vector3* e1, Vector3* e2, Vector3* e3)
	{
		return 0.0f;
	}
}

namespace Mathematics
{
	Vector3 Vec3Mat4Mul(Vector3& vec, Matrix4& mat)
	{
		Vector3 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];
		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];
		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];

		return retVec;
	}

	Vector3 CatMullRomSpline(std::vector<Vector3>& points, float t)
	{

		float length = static_cast<float>(points.size());
		float progress = (length - 1) * t;
		float index = std::floor(progress);
		float weight = progress - index;

		if (MyMathUtility::Approximately(weight, 0.0f) && index >= length - 1)
		{
			index = length - 2;
			weight = 1;
		}

		Vector3 p0 = points[static_cast<size_t>(index)];
		Vector3 p1 = points[static_cast<size_t>(index + 1.0f)];
		Vector3 p2;
		Vector3 p3;

		if (index > 0.0f)
		{
			p2 = 0.5f * (points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index - 1.0f)]);
		}
		else
		{
			p2 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		if (index < length - 2.0f)
		{
			p3 = 0.5f * (points[static_cast<size_t>(index + 2.0f)] - points[static_cast<size_t>(index)]);
		}
		else
		{
			p3 = points[static_cast<size_t>(index + 1.0f)] - points[static_cast<size_t>(index)];
		}

		return MyMathUtility::HermiteGetPoint(p0, p1, p2, p3, weight);
	}

	float LenSegLineOfSeparateAxis(Vector3* sep, Vector3* e1, Vector3* e2, Vector3* e3)
	{
		// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
		float r1 = fabs(sep->dot(*e1));
		float r2 = fabs(sep->dot(*e2));
		float r3 = e3 ? (fabs(sep->dot(*e3))) : 0;
		return r1 + r2 + r3;
	}
}

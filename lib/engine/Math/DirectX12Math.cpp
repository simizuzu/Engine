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

	Matrix4 MakeScaling(Vector3 scale)
	{
		Matrix4 matScale;
		matScale.m[0][0] = scale.x;
		matScale.m[1][1] = scale.y;
		matScale.m[2][2] = scale.z;
		matScale.m[3][3] = 1.0f;

		return matScale;
	}

	Matrix4 MakeRotation(Vector3 rot)
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

	Matrix4 MakeTranslation(Vector3 trans)
	{
		Matrix4 matTrans;
		matTrans = MakeIdentity();
		matTrans.m[3][0] = trans.x;
		matTrans.m[3][1] = trans.y;
		matTrans.m[3][2] = trans.z;
		return matTrans;
	}

	Matrix4 CreateMatrix(const WorldTransform& worldTransform)
	{
		Matrix4 matWorld;

		matWorld = MakeIdentity();
		matWorld = MakeScaling(worldTransform.scale_);
		matWorld = MakeRotation(worldTransform.rotation_);
		matWorld = MakeTranslation(worldTransform.translation_);

		if (worldTransform.parent_ != nullptr)
		{
			matWorld *= worldTransform.parent_->matWorld_;
		}
		
		return matWorld;
	}

	void WorldTransUpdate(WorldTransform& childWorldtrans)
	{
		childWorldtrans.matWorld_ = CreateMatrix(childWorldtrans);			// çáê¨ÇµÇΩçsóÒÇÃåvéZ
		childWorldtrans.matWorld_ *= childWorldtrans.parent_->matWorld_;	// parent_ÇÃÉèÅ[ÉãÉhçsóÒÇÃä|ÇØéZë„ì¸
		childWorldtrans.TransferMatrix();									// çsóÒÇÃì]ëó
	}

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
}
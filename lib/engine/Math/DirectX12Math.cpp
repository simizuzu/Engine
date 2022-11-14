#include "DirectX12Math.h"
#include <cmath>

namespace MyMathUtility
{
	float Vector2Length(const Mathematics::Vector2& v)
	{
		return (float)std::sqrt(v.x * v.x + v.y * v.y);
	}

	float Vector3Length(const Mathematics::Vector3& v)
	{
		return (float)std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	Mathematics::Vector3 MakeNormalize(Mathematics::Vector3 v)
	{
		float len = Vector3Length(v);
		if (len != 0) {
			return v /= len;
		}
		return v;
	}

	Mathematics::Matrix4 MakeIdentity()
	{
		Mathematics::Matrix4 matIdentity;
		matIdentity.m[0][0] = 1.0f;
		matIdentity.m[1][1] = 1.0f;
		matIdentity.m[2][2] = 1.0f;
		matIdentity.m[3][3] = 1.0f;

		return matIdentity;
	}

	Mathematics::Matrix4 MakeScaling(Mathematics::Matrix4& m, Mathematics::Vector3 scale)
	{
		Mathematics::Matrix4 matScale;
		matScale.m[0][0] = scale.x;
		matScale.m[1][1] = scale.y;
		matScale.m[2][2] = scale.z;
		matScale.m[3][3] = 1.0f;

		return matScale;
	}

	Mathematics::Matrix4 MakeRotationZ(Mathematics::Matrix4& m, Mathematics::Vector3 rot)
	{
		Mathematics::Matrix4 matRotZ;
		matRotZ.m[0][0] = cosf(rot.z);
		matRotZ.m[0][1] = sinf(rot.z);
		matRotZ.m[1][1] = cosf(rot.z);
		matRotZ.m[1][0] = -sinf(rot.z);
		matRotZ.m[2][2] = 1.0f;
		matRotZ.m[3][3] = 1.0f;

		return matRotZ;
	}

	Mathematics::Matrix4 MakeRotationX(Mathematics::Matrix4& m, Mathematics::Vector3 rot)
	{
		Mathematics::Matrix4 matRotX;
		matRotX.m[1][1] = cosf(rot.z);
		matRotX.m[1][2] = sinf(rot.z);
		matRotX.m[2][1] = -sinf(rot.z);
		matRotX.m[2][2] = cosf(rot.z);
		matRotX.m[0][0] = 1.0f;
		matRotX.m[3][3] = 1.0f;

		return matRotX;
	}

	Mathematics::Matrix4 MakeRotationY(Mathematics::Matrix4& m, Mathematics::Vector3 rot)
	{
		Mathematics::Matrix4 matRotY;
		matRotY.m[0][0] = cosf(rot.z);
		matRotY.m[0][2] = -sinf(rot.z);
		matRotY.m[2][0] = sinf(rot.z);
		matRotY.m[2][2] = cosf(rot.z);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[3][3] = 1.0f;

		return matRotY;
	}

	//Mathematics::Matrix4 MakeRotation(Mathematics::Matrix4& m, Mathematics::Vector3 rot)
	//{
	//	
	//}

	Mathematics::Matrix4 MakeTranslation(Mathematics::Matrix4& m, Mathematics::Vector3 trans)
	{
		Mathematics::Matrix4 matTrans;
		matTrans = MakeIdentity();
		matTrans.m[3][0] = trans.x;
		matTrans.m[3][1] = trans.y;
		matTrans.m[3][2] = trans.z;
		return matTrans;
	}

	/*Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform)
	{
		Mathematics::Matrix4 matWorld;
		matWorld = MakeIdentity();
		matWorld = MakeScaling()
		return Mathematics::Matrix4();
	}*/

	Mathematics::Matrix4 MatMulVector(Mathematics::Matrix4 m, Mathematics::Vector3 v)
	{
		return Mathematics::Matrix4();
	}

}
#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "WorldTransform.h"

namespace MyMathUtility
{
	// 度からラジアンに変換する定数
	const float PI = 3.141592654f;
	constexpr float degree2Radius = 3.1415926535897931f / 180.0f;
	constexpr float PIHalf = 3.1415926535897931f / 2.0f;

	// 長さを求める(2次元)
	float Vector2Length(const Mathematics::Vector2& v);
	// 長さを求める(3次元)
	float Vector3Length(const Mathematics::Vector3& v);

	// 正規化する
	Mathematics::Vector3 MakeNormalize(Mathematics::Vector3 v);

	// 単位行列を求める
	Mathematics::Matrix4 MakeIdentity();
	// 拡大縮小を求める
	Mathematics::Matrix4 MakeScaling(Mathematics::Matrix4 m, Mathematics::Vector3 scale);
	// 回転行列を求める
	Mathematics::Matrix4 MakeRotationZ(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotationX(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotationY(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	Mathematics::Matrix4 MakeRotation(Mathematics::Matrix4 m, Mathematics::Vector3 rot);
	// 平行移動行列を求める
	Mathematics::Matrix4 MakeTranslation(Mathematics::Matrix4 m, Mathematics::Vector3 trans);
	// ワールド行列の計算
	Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);
	// ベクトルと行列の掛け算
	Mathematics::Matrix4 MatMulVector(Mathematics::Matrix4 m, Mathematics::Vector3 v);

	Mathematics::Matrix4 MakeOrthographic(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);

	// 線形補間
	float Lerp(float a, float b, float t);

} // namespace MyMathUtility
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
	Mathematics::Matrix4 MakeScaling(Mathematics::Vector3 scale);
	// 回転行列を求める
	Mathematics::Matrix4 MakeRotation(Mathematics::Vector3 rot);
	// 平行移動行列を求める
	Mathematics::Matrix4 MakeTranslation(Mathematics::Vector3 trans);
	// ワールド行列の計算
	Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	/// <summary>
	/// 1つ分のワールドトランスフォーム更新関数
	/// </summary>
	/// <param name="childWorldtrans">子のworldTransform</param>
	void WorldTransUpdate(WorldTransform& childWorldtrans);

	// ベクトルと行列の掛け算
	Mathematics::Matrix4 MatMulVector(Mathematics::Matrix4 m, Mathematics::Vector3 v);

	// 平行投影変換(左手系)
	void MakeOrthogonalL(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);
	// 平行投影変換(左手系)
	void MakeOrthogonalR(float left, float right, float bottom, float top, float near_, float far_, Mathematics::Matrix4& matrix);

	// ビュー行列の作成
	Mathematics::Matrix4 MakeLookAtLH( Mathematics::Vector3& eye,  Mathematics::Vector3& target, Mathematics::Vector3& up);
	// 透視投影作成
	Mathematics::Matrix4 MakePerspective(float fogAngleY, float aspectRatio, float nearZ, float farZ);
	// 逆行列
	Mathematics::Matrix4 MakeInverse(Mathematics::Matrix4& mat);

	// 線形補間
	float Lerp(float a, float b, float t);

} // namespace MyMathUtility
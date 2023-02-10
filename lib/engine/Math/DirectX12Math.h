#pragma once
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace MyMathUtility
{
	// 度からラジアンに変換する定数
	const float PI = 3.141592654f;
	constexpr float degree2Radius = 3.1415926535897931f / 180.0f;
	constexpr float PIHalf = 3.1415926535897931f / 2.0f;

	//ε(イプシロン)
	constexpr float EPSILON = 2.2204460492503131E-16f;

	// 長さを求める(2次元)
	float Vector2Length(const Mathematics::Vector2& v);
	// 長さを求める(3次元)
	float Vector3Length(const Mathematics::Vector3& v);

	// 正規化する
	Mathematics::Vector3 MakeNormalize(Mathematics::Vector3 v);

	// 単位行列を求める
	Mathematics::Matrix4 MakeIdentity();
	// 拡大縮小を求める
	Mathematics::Matrix4 MakeScaling(const Mathematics::Vector3& scale);
	// 回転行列を求める
	Mathematics::Matrix4 MakeRotation(const Mathematics::Vector3& rot);
	// 平行移動行列を求める
	Mathematics::Matrix4 MakeTranslation(const Mathematics::Vector3& trans);
	//// ワールド行列の計算
	//Mathematics::Matrix4 CreateMatrix(const WorldTransform& worldTransform);

	///// <summary>
	///// 1つ分のワールドトランスフォーム更新関数
	///// </summary>
	///// <param name="childWorldtrans">子のworldTransform</param>
	//void WorldTransUpdate(WorldTransform& childWorldtrans);

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

	Mathematics::Vector3 Dot(const Mathematics::Vector3& a, const Mathematics::Vector3 b);

	// 値が等しいか確認する
	bool Approximately(float a, float b);

	// 線形補間
	float Lerp(float a, float b, float t);
	Mathematics::Vector3 Lerp(Mathematics::Vector3 a, Mathematics::Vector3 b, float t);

	/// <summary>
	/// エルミート曲線
	/// </summary>
	/// <param name="p0">制御点</param>
	/// <param name="p1">制御点</param>
	/// <param name="v0">制御点</param>
	/// <param name="v1">制御点</param>
	/// <param name="t">時間(0.0～1.0)</param>
	/// <returns></returns>
	Mathematics::Vector3 HermiteGetPoint(Mathematics::Vector3 p0, Mathematics::Vector3 p1, Mathematics::Vector3 v0, Mathematics::Vector3 v1, float t);

	// Sin,Cos,Tan関数
	float Sin(float sin);
	float Cos(float cos);
	float Tan(float tan);

	float Asin(float sin);
	float Acos(float cos);
	float Atan(float tan);
	float Atan2(float y, float x);

	void Complement(float& x1, float x2, float flame);

	float Clamp(float Value, const float low, const float high);
	float Clamp0To1(float val);

} // namespace MyMathUtility

namespace Mathematics
{
	// ベクトルと行列の掛け算
	Vector3 Vec3Mat4Mul(Vector3& vec, Matrix4& mat);

	// キャットムルーロムスプライン曲線
	Vector3 CatMullRomSpline(std::vector<Vector3>& points, float t);

	/// 分離軸に投影された軸成分から投影線分長を算出
	float LenSegLineOfSeparateAxis(Vector3* sep, Vector3* e1, Vector3* e2, Vector3* e3 = 0);
}
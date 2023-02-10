#pragma once
#include <vector>
#include <array>
#include <string>
#include "Vector3.h"
#include "Vector4.h"
#include "Object3d.h"

/// <summary>
/// 衝突判定基底クラス
/// </summary>
class BaseCollision
{
protected:

	uint32_t collisionAttribute_ = 0xffffffff;
	// 衝突マスク(相手)
	uint32_t collisionMask_ = 0xffffffff;

	// 名前(自分)
	std::string collsionName_;
	// 名前(相手)
	char opponentCollsionName_[256];

	BaseCollision() = default;
	virtual ~BaseCollision() = default;

public:
	// 衝突時に呼ばれる関数
	virtual void OnCollision() = 0;
	// 衝突属性(自分)を取得
	const uint32_t GetCollisionAttribute();
	// 衝突属性(自分)を取得
	void SetCollisionAttribute(uint32_t collisionAttribute);
	// 衝突属性(相手)を取得
	const uint32_t GetCollisionMask();
	// 衝突属性(相手)を設定
	void SetCollisionMask(uint32_t collisionMask);

	// 名前(自分)
	void SetCollsionName(std::string name);
	std::string GetCollsionName();

	// 名前(相手:Opponent)
	void SetOppCollsionName(std::string name);
	std::string GetOppCollsionName();
};

struct AABB
{
	// 中心座標
	Mathematics::Vector3 center;
	// サイズ
	Mathematics::Vector3 size;
};

struct Sphere
{
	// 中心座標
	Mathematics::Vector4 center;
	// 半径
	float radius;
};

struct Plane
{
	Mathematics::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
	float distance = 0.0f;
};

class BoundingBox : public BaseCollision
{
protected:
	// 位置
	Mathematics::Vector3 center = {};
	// 方向ベクトル
	Mathematics::Vector3 directionVec[3];
	// 各軸方向の長さ
	float length[3]{};

public:
	// 指定軸番号の方向ベクトルを取得
	const Mathematics::Vector3 GetDirectVec(uint16_t element);
	// 指定軸方向の長さを取得
	const float GetLength(uint16_t element);
	// 中心からの位置を取得
	const Mathematics::Vector3 GetCenter();
	// 衝突時に呼ばれる関数
	virtual void OnCollision() {};

public:
	/// <summary>
	/// AABBとAABBの当たり判定
	/// </summary>
	/// <param name="aabb1">1つ目のAABB</param>
	/// <param name="aabb2">2つ目のAABB</param>
	/// <returns>true</returns>
	bool CheckAABBToAABB(AABB& aabb1, AABB& aabb2);

	/// <summary>
	/// AABBと球の当たり判定
	/// </summary>
	/// <param name="aabb1">1つ目のAABB</param>
	/// <param name="aabb2">球</param>
	/// <returns>false</returns>
	bool CheckAABBToSphere(AABB& aabb,Sphere& sphere);

public:
	/// <summary>
	/// OBBを作成
	/// </summary>
	/// <param name="vertex">頂点</param>
	/// <param name="transform">ワールドトランスフォーム</param>
	void CreateOBB(std::vector<VertexPosNormalUv> vertex, Object3d& transform);

	/// <summary>
	/// OBBの更新
	/// </summary>
	/// <param name="transform">ワールドトランスフォーム</param>
	void UpdateOBB(Object3d& transform);
};
#pragma once
#include"BranchPoint.h"

class SpeedUpChance
{
public:

	SpeedUpChance() = default;
	~SpeedUpChance() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(RailCamera* railCamera);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(Camera* camera);

private:
	std::list<std::unique_ptr<BranchPoint>>branchPoints;

	//本体
	std::unique_ptr<Model> firstModel_;
	std::unique_ptr<Object3d> firstObject_;

	std::unique_ptr<Model> secondModel_;
	std::unique_ptr<Object3d> secondObject_;

	//コピーコンストラクタ・代入演算子削除
	SpeedUpChance& operator=(const SpeedUpChance&) = delete;
	SpeedUpChance(const SpeedUpChance&) = delete;
};


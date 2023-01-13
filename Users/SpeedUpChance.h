#pragma once
#include"BranchPoint.h"

class SpeedUpChance
{
public:

	SpeedUpChance() = default;
	~SpeedUpChance() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(RailCamera* railCamera);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(Player* player);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(Camera* camera);

private:
	std::list<std::unique_ptr<BranchPoint>>branchPoints;

	//�{��
	std::unique_ptr<Model> firstModel_;
	std::unique_ptr<Object3d> firstObject_;

	std::unique_ptr<Model> secondModel_;
	std::unique_ptr<Object3d> secondObject_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SpeedUpChance& operator=(const SpeedUpChance&) = delete;
	SpeedUpChance(const SpeedUpChance&) = delete;
};


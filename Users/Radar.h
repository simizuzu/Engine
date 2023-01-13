#pragma once
#include <memory>
#include <list>

#include "Sprite.h"
#include "TextureManager.h"
#include "Enemy.h"
#include "Object3d.h"

struct RadarData
{
	TextureData radarTex;
	TextureData radarPlayerTex;
	TextureData radarEnemyTex;
};

class Radar
{
private:
	// �w�i�G
	std::unique_ptr<Sprite> radar_;
	TextureData radarTex;
	Object3d radarTrans;

	// �v���C���[�G
	std::unique_ptr<Sprite> radarPlayer_;
	TextureData radarPlayerTex;
	Object3d radarPlayerTrans;

	// �G�G
	std::list<std::unique_ptr<Sprite>> radarEnemys_;
	TextureData radarEnemyTex_;

public:
	Radar() = default;
	~Radar() = default;
	void Initialize(RadarData& radarData);
	void Update(float playerX, float playerZ, float playerAngle, std::list<std::shared_ptr<Enemy>>enemys);
	void Draw();

	//�Q�b�^�[
	static Radar* GetInstance();

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Radar& operator=(const Radar&) = delete;
	Radar(const Radar&) = delete;
};


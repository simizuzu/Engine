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
	// 背景絵
	std::unique_ptr<Sprite> radar_;
	TextureData radarTex;
	Object3d radarTrans;

	// プレイヤー絵
	std::unique_ptr<Sprite> radarPlayer_;
	TextureData radarPlayerTex;
	Object3d radarPlayerTrans;

	// 敵絵
	std::list<std::unique_ptr<Sprite>> radarEnemys_;
	TextureData radarEnemyTex_;

public:
	Radar() = default;
	~Radar() = default;
	void Initialize(RadarData& radarData);
	void Update(float playerX, float playerZ, float playerAngle, std::list<std::shared_ptr<Enemy>>enemys);
	void Draw();

	//ゲッター
	static Radar* GetInstance();

private:
	//コピーコンストラクタ・代入演算子削除
	Radar& operator=(const Radar&) = delete;
	Radar(const Radar&) = delete;
};


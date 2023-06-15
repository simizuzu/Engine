#pragma once
#include "AvoidWarning.h"
#include "Camera.h"
#include "EngineUtility.h"

class WorldTransform
{

public:
	//初期化
	void Initialize();
	//更新
	void Update(Camera* camera,bool billboradFlag = false);


public:	//セッター・ゲッター
	void SetTranslation(MyMath::Vector3 translation);
	void SetScale(MyMath::Vector3 scale);
	void SetRotation(MyMath::Vector3 rotation);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuAddress();

private: //メンバ関数
	//定数バッファ生成
	void CreateConstBuffer();

private:
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer_;
	WorldvViewProCamera constBuffMap;

public:
	//ローカル座標
	MyMath::Vector3 translation_ = { 0.0f,0.0f,0.0f };
	//X,Y,Z軸回りのローカル回転角
	MyMath::Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	//ローカルスケール
	MyMath::Vector3 scale_ = { 1.0f,1.0f,1.0f };

	MyMath::Matrix4 matWorld;

	const WorldTransform* parent = nullptr;
};


#pragma once
#include "DirectXCommon.h"

#include "Matrix4.h"
#include "Vector3.h"
#include "DirectX12Math.h"

/// <summary>
/// ライト
/// </summary>
class Light
{
public:
	struct ConstBufferData
	{
		Mathematics::Matrix4 lightVec;		//ライトへの方向を表すベクトル
		Mathematics::Vector3 lightColor;	//ライトの色
	};

public: //静的メンバ関数
	static void StaticInitialize(DirectXCommon* device);

private: //静的メンバ変数
	//デバイス
	static DirectXCommon* device_;

public:
	void Initialize();

private: //メンバ変数
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向（単位ベクトル）
	Mathematics::Matrix4 lightdir = MyMathUtility::MakeIdentity();
	//ライト色
	Mathematics::Vector3 lightColor = { 1.0f,1.0f,1.0f };
	//ダーティフラグ
	bool dirty = false;
};


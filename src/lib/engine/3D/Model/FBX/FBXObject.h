#pragma once
#include "FbxModel.h"
#include "DirectX12Math.h"


class FbxObject
{
public: //静的メンバ関数
	static void StaticInitialize(ID3D12Device* device);

	//パイプライン初期化
	static void CrateGrapicsPipeline();

private: //静的メンバ変数
	//デバイス
	static ID3D12Device* device_;

public:
	struct ConstBufferDataTransformFbx
	{
		MyMath::Matrix4 viewproj;
		MyMath::Matrix4 world;
		MyMath::Vector3 cameraPos;
	};

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

protected:
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffTransform;
};
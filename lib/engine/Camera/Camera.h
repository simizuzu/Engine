#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "DirectX12Math.h"

struct ConstBufferDataViewProjection
{
	// ワールド行列
	Mathematics::Matrix4 world;
	// ワールド座標
	Mathematics::Matrix4 matWorld;

	// ワールド → ビュー変換行列
	Mathematics::Matrix4 view;
	// ビュー → プロジェクション変換行列
	Mathematics::Matrix4 projection;
	// カメラ座標（ワールド座標）
	Mathematics::Vector3 cameraPos;
};

struct ViewProjection
{
	// 定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	// マッピング済みアドレス
	ConstBufferDataViewProjection* constBuffMap = nullptr;
};

class Camera
{
public:
#pragma region ビュー行列設定
	// 視点座標
	Mathematics::Vector3 eye_;
	// 注視点座標
	Mathematics::Vector3 target_;
	// 上方向ベクトル
	Mathematics::Vector3 up_;
#pragma endregion

private:
#pragma region 射影行列設定
	// カメラ画角
	float fovAngleY = MyMathUtility::degree2Radius * 45.0f;
	// 手前
	float nearZ_ = 0.1f;
	// 奥行き
	float farZ_ = 1000.0f;
	// アスペクト比(画面横幅/画面縦幅)
	float aspect = 0.0f;
#pragma endregion
	// ビュー行列
	Mathematics::Matrix4 matView_;
	// ビュー逆行列
	Mathematics::Matrix4 matViewInverse_;
	// 射影行列
	Mathematics::Matrix4 matProjection_;;
	// カメラ距離
	float distance = 50.0f;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 定数バッファ生成
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// マッピング
	/// </summary>
	void Map();
	/// <summary>
	/// ビュー行列の更新
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// ビュー行列の転送
	/// </summary>
	void TransferMatrix();

public:
	const Mathematics::Matrix4& GetMatView();
	const Mathematics::Matrix4& GetMatViewInverse();
	const Mathematics::Matrix4& GetMatProjection();

	const Mathematics::Vector3& GetEye();
	const Mathematics::Vector3& GetTarget();
	const Mathematics::Vector3& GetUp();

	void SetEye(const Mathematics::Vector3& eye);
	void SetTarget(const Mathematics::Vector3& target);
	void SetUp(const Mathematics::Vector3& up);
	void SetFarZ(const float& farZ);
	void SetNearZ(const float& nearZ);
};
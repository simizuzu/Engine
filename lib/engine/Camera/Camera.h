#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "DirectX12Math.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "EngineUtility.h"

class Camera
{
public:
#pragma region ビュー行列設定
	// 視点座標
	MyMath::Vector3 eye_;
	// 注視点座標
	MyMath::Vector3 target_;
	// 上方向ベクトル
	MyMath::Vector3 up_;
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
	MyMath::Matrix4 matView_;
	// ビュー逆行列
	MyMath::Matrix4 matViewInverse_;
	// 射影行列
	MyMath::Matrix4 matProjection_;;
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
	const MyMath::Matrix4& GetMatView();
	const MyMath::Matrix4& GetMatViewInverse();
	const MyMath::Matrix4& GetMatProjection();

	const MyMath::Vector3& GetEye();
	const MyMath::Vector3& GetTarget();
	const MyMath::Vector3& GetUp();

	void SetEye(const MyMath::Vector3& eye);
	void SetTarget(const MyMath::Vector3& target);
	void SetUp(const MyMath::Vector3& up);
	void SetFarZ(const float& farZ);
	void SetNearZ(const float& nearZ);
};
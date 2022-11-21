#pragma once
#include "DirectX12Math.h"

struct ConstBufferDataViewProjection
{
	Mathematics::Matrix4 view;       // ワールド → ビュー変換行列
	Mathematics::Matrix4 projection; // ビュー → プロジェクション変換行列
	Mathematics::Vector3 cameraPos;  // カメラ座標（ワールド座標）
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
private:
#pragma region ビュー行列設定
	// 視点座標
	Mathematics::Vector3 eye_ = { 0.0f, 0.0f, -100.0f };
	// 注視点座標
	Mathematics::Vector3 target_ = { 0, 0, 0 };
	// 上方向ベクトル
	Mathematics::Vector3 up_ = { 0, 1, 0 };
#pragma endregion

#pragma region 射影行列設定
	// カメラ画角
	float fovAngleY = 0.0f;
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
	const Mathematics::Matrix4& GetMatView() { return matView_; }
	const Mathematics::Matrix4& GetMatViewInverse() { return matViewInverse_; }
	const Mathematics::Matrix4& GetMatProjection() { return matProjection_; }

	const Mathematics::Vector3& GetEye() { return eye_; }
	const Mathematics::Vector3& GetTarget() { return target_; }
	const Mathematics::Vector3& GetUp() { return up_; }

	void SetEye(const Mathematics::Vector3& eye) { eye_ = eye; }
	void SetTarget(const Mathematics::Vector3& target) { target_ = target; }
	void SetUp(const Mathematics::Vector3& up) { up_ = up; }
	void SetFarZ(const float& farZ) { farZ_ = farZ; }
	void SetNearZ(const float& nearZ) { nearZ_ = nearZ; }
};
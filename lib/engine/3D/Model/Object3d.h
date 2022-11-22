#pragma once
#include <d3d12.h>
#include <memory>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"
#include "Shader.h"
#include "WorldTransform.h"
#include "Camera.h"

#include "Matrix4.h"

class Object3d
{
private: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		Mathematics::Matrix4 mat;	// 3D変換行列
	};

public: // 静的メンバ関数
	static void StaticInitialize(ID3D12Device* device, int width, int height);

	static void CreateGraphicsPipeline();

	static Object3d* Create();

private:
	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="width">画面縦幅</param>
	/// <param name="hegiht">画面横幅</param>
	static void InitializeCamera();

	// デバイス
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// コマンドリスト
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	// パイプラインステート
	static RootsigSetPip pip;
	// 視点座標
	static Mathematics::Vector3 eye;
	// 注視点座標
	static Mathematics::Vector3 target;
	// 上方向ベクトル
	static Mathematics::Vector3 up;
	// パイプライン
	static std::unique_ptr<Pipeline> pipeline;
	// カメラ
	static Camera* camera;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// setter
	void SetModel(Model* model) { this->model = model; }
	void SetPosition(Mathematics::Vector3 position_) { position_ = position; }
	void SetScale(Mathematics::Vector3 scale_) { scale_ = scale; }
	void SetRotation(Mathematics::Vector3 rotation_) { rotation_ = rotation; }

private: // メンバ変数
	// 定数バッファ
	ComPtr <ID3D12Resource> constBuffB0;
	// 色
	Mathematics::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
	// ローカルスケール
	Mathematics::Vector3 scale = { 1.0f,1.0f,1.0f };
	// X,Y,Z軸回りのローカル回転角
	Mathematics::Vector3 rotation = { 0.0f,0.0f,0.0f };
	// ローカル座標
	Mathematics::Vector3 position = { 0.0f,0.0f,0.0f };
	// ワールド変換行列
	Mathematics::Matrix4 matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	// モデル
	Model* model = nullptr;
	// ワールド行列
	WorldTransform* worldTransform_ = nullptr;
};
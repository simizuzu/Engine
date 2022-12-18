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
	void SetModel(Model* model);
	void SetTranslation(Mathematics::Vector3 translation_);
	void SetScale(Mathematics::Vector3 scale_);
	void SetRotation(Mathematics::Vector3 rotation_);

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
	Mathematics::Vector3 translation = { 0.0f,0.0f,0.0f };
	// ワールド変換行列
	Mathematics::Matrix4 matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	// モデル
	Model* model = nullptr;
	// ワールド行列
	WorldTransform* worldTransform_ = nullptr;
};
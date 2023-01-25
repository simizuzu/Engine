#pragma once
#include <d3d12.h>
#include <memory>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"
#include "Shader.h"

#include "lib/engine/Camera/Camera.h"
#include "Matrix4.h"

class Object3d
{
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
	void SetPosition(Mathematics::Vector3 position_);
	void SetScale(Mathematics::Vector3 scale_);
	void SetRotation(Mathematics::Vector3 rotation_);

public:
	// 定数バッファ
	Microsoft::WRL::ComPtr <ID3D12Resource> constBuffB0;
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
};

namespace Mathematics
{
	Vector3 GetWorldPosition(Object3d& transform);
	Matrix4 MakeWorldMatrix4(Object3d& transform);
}
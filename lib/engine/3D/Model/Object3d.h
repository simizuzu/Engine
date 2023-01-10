#pragma once
#include <d3d12.h>
#include <memory>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"
#include "Shader.h"
#include "WorldTransform.h"

#include "Matrix4.h"

class Object3d
{
private: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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
	//void Update(Camera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(WorldTransform* worldTransform);

	// setter
	void SetModel(Model* model);

private:
	// モデル
	Model* model = nullptr;
	// ワールドトランスフォーム
	WorldTransform* worldTransform_ = nullptr;
};
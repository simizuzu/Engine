#pragma once
#include <d3d12.h>

#include "DirectXCommon.h"
#include "Model.h"
#include "Pipeline.h"

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

private:// 静的メンバ関数(非公開)
	static void UpdateViewMatrix();

private: // 静的メンバ変数
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;
	// コマンドリスト
	static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList_;
	

	// クラス呼び出し
	static Pipeline* pipeline;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	bool Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


};
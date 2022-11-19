#pragma once

#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

#include "DirectX12Math.h"
#include "DirectXCommon.h"
#include "WinApp.h"



class Object3d
{
private: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 静的メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dxCommon">: デバイス</param>
	/// <param name="width">: 横</param>
	/// <param name="height">: 縦</param>
	static void StaticInitialize(DirectXCommon* device,WinApp* width, WinApp* height);

	static Object3d* Create();

	/// <summary>
	/// 描画前処理
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // クラス呼び出し
	DirectXCommon* dxCommon_ = nullptr;
};
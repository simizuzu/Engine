#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>

#include "DirectX12Math.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

class PostEffect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

	/// <summary>
	/// 描画コマンドの実行
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);
};


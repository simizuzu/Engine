﻿#pragma once
#include <directx/d3d12.h>
#include <wrl.h>

class Shader
{
public: // メンバ関数
	// スプライト用
	static void CreateSpriteShade(Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob, Microsoft::WRL::ComPtr<ID3DBlob>& psBlob);
	// 3Dオブジェクト用
	static void CreateObjShade(Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob, Microsoft::WRL::ComPtr<ID3DBlob>& psBlob);
	// パーティクル用
	static void CreateParticleShade(Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob, Microsoft::WRL::ComPtr<ID3DBlob>& psBlob, Microsoft::WRL::ComPtr<ID3DBlob>& gsBlob);
	static void CreatePostEffectShade(Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob,Microsoft::WRL::ComPtr<ID3DBlob>& psBlob);

};

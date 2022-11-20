#pragma once

#include "TextureManager.h"

class Shader
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	// スプライト用
	void CreateSpriteShade(ComPtr<ID3DBlob>& vsBlob, ComPtr<ID3DBlob>& psBlob);
	// 3Dオブジェクト用
	void CreateObjShade(ComPtr<ID3DBlob>& vsBlob, ComPtr<ID3DBlob>& psBlob);


};
#pragma once

#include "TextureManager.h"

class Shader
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // メンバ変数
	// 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> vsBlob;
	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;
	// エラーオブジェクト
	ComPtr<ID3DBlob> errorBlob;

public: // メンバ関数
	void CreateSpriteShade();

};
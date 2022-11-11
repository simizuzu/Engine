#pragma once

#include <cassert>
#include "DirectXCommon.h"
#include "Vector3.h"
#include "Matrix4.h"

struct ConstBufferDataWorldTransform
{
	Mathematics::Matrix4 matWorld;
};

class WorldTransform
{
public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファの生成
	/// </summary>
	void CreateConstBuff();

	/// <summary>
	/// マッピングする
	/// </summary>
	void Map();

	/// <summary>
	/// 行列を転送する
	/// </summary>
	void TransferMatrix();

private:
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	// マッピング済みアドレス
	ConstBufferDataWorldTransform* constMap_ = nullptr;
	// ローカルスケール
	Mathematics::Vector3 scale_ = { 1, 1, 1 };
	// X,Y,Z軸回りのローカル回転角
	Mathematics::Vector3 rotation_ = { 0, 0, 0 };
	// ローカル座標
	Mathematics::Vector3 translation_ = { 0, 0, 0 };
	// ローカル → ワールド変換行列
	Mathematics::Matrix4 matWorld_;
	// 親となるワールド変換へのポインタ
	const WorldTransform* parent_ = nullptr;

	// クラス呼び出し
	DirectXCommon* dxCommon_ = nullptr;
};
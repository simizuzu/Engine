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

// 2D変換行列(定数バッファ)
struct ConstBufferData
{
	Mathematics::Vector4 color;
	Mathematics::Matrix4 mat;
};

/// 頂点データ構造体
struct PosUvColor
{
	Mathematics::Vector3 pos;
	Mathematics::Vector2 uv;
	//Mathematics::Vector4 color;
};

class Sprite
{
public:
	// 頂点番号
	enum VertexNumber {
		LB,	// 左下
		LT,	// 左上
		RB,	// 右下
		RT,	// 右上
	};

public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device_;
	// デスクリプタサイズ
	static UINT descriptorSize_;
	// コマンドリスト
	static ID3D12GraphicsCommandList* commandList_;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature_;
	// プロジェクション行列
	static Mathematics::Matrix4 matProjection_;
	// パイプラインステート
	static std::array<RootsigSetPip, 6> pipelineState;
	
	static std::array<RootsigSetPip, 6>& pipeline;

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点マップ
	PosUvColor* vertMap;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファの生成
	Microsoft::WRL::ComPtr<ID3D12Resource>indexBuff;
	//インデックスバッファをマッピング
	uint16_t* indexMap;
	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	// エラーオブジェクト
	ComPtr<ID3DBlob> errorBlob;
	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	// インプットレイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout{};

	// 座標
	Mathematics::Vector2 position_ = { 0.0f,0.0f };
	// 色
	Mathematics::Vector4 color_ = { 1, 1, 1, 1 };

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource>constBuff;
	Mathematics::Matrix4* constBuffMap = nullptr;

	// 角度
	float rotation_ = 0.0f;
	// 表示サイズ(単位はpixel)
	Mathematics::Vector2 size_ = { 100.0f,100.0f };
	// テクスチャ番号
	uint32_t textureIndex_ = 0;
	// ブレンドモード
	int blendMode = (int)BlendMode::Alpha;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Mathematics::Vector2 pos, Mathematics::Vector2 scale, float rot);

	/// <summary>
	/// 描画
	/// </summary>
	void DrawCommandList(TextureData textureData);

	/// <summary>
	/// スプライト描画
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void DrawSprite(
		TextureData& textureData, Mathematics::Vector2 position, Mathematics::Vector2 scale = { 1.0f,1.0f }, float rotation = 0.0f,
		Mathematics::Vector2 anchorpoint = { 0.0f,0.0f }, bool flipX = false, bool flipY = false);

	/// <summary>
	/// 頂点バッファ関連の初期化
	/// </summary>
	void CreateVertexIndexBuff();

	/// <summary>
	/// 定数バッファ作成
	/// </summary>
	void CreateConstBuff();

public: // 静的メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	static void StaticInitialize();

public: // setter,getter
	/// <summary>
	/// 座標をセット
	/// </summary>
	/// <param name="position">: 座標{ x,y }</param>
	void SetPosiotion(const Mathematics::Vector2& position) { position_ = position; }

	/// <summary>
	/// 回転角をセット
	/// </summary>
	/// <param name="rotation">: 角度</param>
	void SetRotation(float rotation) { rotation_ = rotation; }

	/// <summary>
	/// スプライトの大きさをセット
	/// </summary>
	/// <param name="rotation">サイズ</param>
	void SetSize(const Mathematics::Vector2& size) { size_ = size; }

	/// <summary>
	/// スプライトの色をセット
	/// </summary>
	/// <param name="color">: 色{ red,blue,green,alpha }</param>
	void SetColor(const Mathematics::Vector4& color) { color_ = color; }

	/// <summary>
	/// テクスチャ番号をセット
	/// </summary>
	/// <param name="textureIndex">: テクスチャ番号</param>
	void SetTextureIndex(uint32_t textureIndex) { textureIndex_ = textureIndex; }

	/// <summary>
	/// ブレンドを設定
	/// </summary>
	void SetBlendMode(BlendMode mode);

	// 座標
	const Mathematics::Vector2& GetPosition() const { return position_; }
	// 角度
	float GetRotation() const { return rotation_; }
	// 色
	const Mathematics::Vector4& GetColor() const { return color_; }
	// サイズ
	const Mathematics::Vector2& GetSize() const { return size_; }
	// テクスチャ番号
	uint32_t GetTextureIndex() { return textureIndex_; }

private: // クラス呼び出し
	TextureManager* textureManager_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	static Shader* shader_;
	static Pipeline* pipeline_;
	static WinApp* winApp_;

	//TextureData textureData;
};
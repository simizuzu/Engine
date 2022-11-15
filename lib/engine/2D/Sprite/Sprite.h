#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>

#include "TextureManager.h"
#include "DirectXCommon.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

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

	enum class BlendMode
	{
		None,	// ブレンド無し
		Alpha,	// アルファ
		Add,	// 加算
		Sub,	// 減算
		Mul,	// 乗算
		Inv,	// 色反転

		CountOfBlendMode, // 最大ブレンドモード数
	};

public: 
	
	/// <summary>
	/// 頂点データ構造体
	/// </summary>
	struct VertexPosUv
	{
		Mathematics::Vector3 pos;
		Mathematics::Vector2 uv;
	};

	struct ConstBufferData
	{
		Mathematics::Vector4 color;
		Mathematics::Matrix4 mat;
	};

public: // エイリアステンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // メンバ変数
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> vsBlob;
	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;
	// エラーオブジェクト
	ComPtr<ID3DBlob> errorBlob;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	// ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	// パイプラインステート
	ComPtr<ID3D12PipelineState> pipelineState;

	D3D12_INPUT_ELEMENT_DESC inputLayout{};
	// 座標
	Mathematics::Vector2 position_ = { 0.0f,0.0f };
	// 色
	Mathematics::Vector4 color_ = { 1, 1, 1, 1 };
	// 角度
	float rotation_ = 0.0f;
	// 表示サイズ(単位はpixel)
	Mathematics::Vector2 size_ = { 100.0f,100.0f };
	// テクスチャ番号
	uint32_t textureIndex_ = 0;

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

	/// <summary>
	/// 頂点バッファ関連の初期化
	/// </summary>
	void InitializeVertexBuff();

	/// <summary>
	/// シェーダの読み込み関連の初期化
	/// </summary>
	void InitializeShadeLoad();

public:
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList, BlendMode blendMode = BlendMode::None);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

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

#pragma region pipelineクラス用
	// 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> GetVsBlob() { return vsBlob; }
	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> GetPsBlob() { return psBlob; }
	// エラーオブジェクト
	ComPtr<ID3DBlob> GetErrorBlob() { return errorBlob; }

#pragma endregion

private: // クラス呼び出し
	TextureManager* textureManager_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Shader* shader_ = nullptr;
	Pipeline* pipeline_ = nullptr;
};
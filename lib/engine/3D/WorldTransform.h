//#pragma once
//
//#include <cassert>
//#include "DirectXCommon.h"
//#include "Vector3.h"
//#include "Matrix4.h"
//#include "Camera.h"
//
//class WorldTransform
//{
//public: // メンバ関数
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize();
//
//	/// <summary>
//	/// ワールド行列の合成
//	/// </summary>
//	/// <param name="camera"></param>
//	void Update();
//
//	/// <summary>
//	/// 定数バッファの生成
//	/// </summary>
//	void CreateConstBuff();
//
//	/// <summary>
//	/// 行列を転送する
//	/// </summary>
//	void TransferMatrix(Camera* camera);
//
//public: // setter
//	void SetTranslation(Mathematics::Vector3 translation);
//	void SetScale(Mathematics::Vector3 scale);
//	void SetRotation(Mathematics::Vector3 rotation);
//
//public: // getter
//	ID3D12Resource* GetConstBuff();
//
//private:
//	// 定数バッファ
//	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
//	// マッピング済みアドレス
//	ConstBufferDataViewProjection* constMap_ = nullptr;
//
//	//初期化用のビュー行列計算
//	static Mathematics::Matrix4 defaultViewMat;
//	//初期化用のプロジェクション行列計算
//	static Mathematics::Matrix4 defaultProjectionMat;
//
//public:
//	// ローカルスケール
//	Mathematics::Vector3 scale_ = { 1, 1, 1 };
//	// X,Y,Z軸回りのローカル回転角
//	Mathematics::Vector3 rotation_ = { 0, 0, 0 };
//	// ローカル座標
//	Mathematics::Vector3 translation_ = { 0, 0, 0 };
//	// ローカル → ワールド変換行列
//	Mathematics::Matrix4 matWorld_;
//	// 親となるワールド変換へのポインタ
//	const WorldTransform* parent_ = nullptr;
//
//	// デバイス
//	DirectXCommon* device_ = nullptr;
//};
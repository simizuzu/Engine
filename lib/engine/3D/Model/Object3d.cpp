#include "Object3d.h"
#include <windows.h>

#include "DirectX12Math.h"

/// <summary>
/// 静的メンバ変数の実態
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> Object3d::device_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Object3d::cmdList_;
RootsigSetPip Object3d::pip;

void Object3d::StaticInitialize(ID3D12Device* device, int width, int height)
{
	// nullptrチェック
	assert(device);

	Object3d::device_ = device;

	// グラフィックスパイプラインの生成
	CreateGraphicsPipeline();

	Model::SetDevice(device);
}

void Object3d::CreateGraphicsPipeline()
{
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト

	Shader::CreateObjShade(vsBlob, psBlob);

	Pipeline::CreateObjPipeline(vsBlob.Get(), psBlob.Get(), BlendMode::None, device_.Get(),pip);
}

Object3d* Object3d::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Object3d* object3d = new Object3d();
	if (object3d == nullptr)
	{
		return nullptr;
	}

	// 初期化
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	return object3d;
}

bool Object3d::Initialize()
{
	worldTransform_->CreateConstBuff();
}

//void Object3d::Update(Camera* camera)
//{
//	HRESULT result;
//	Mathematics::Matrix4 matScale, matRot, matTrans;
//
//	// スケール、回転、平行移動行列の計算
//	matScale = MyMathUtility::MakeScaling(scale);
//	matRot = MyMathUtility::MakeIdentity();
//	matRot = MyMathUtility::MakeRotation(rotation);
//	matTrans = MyMathUtility::MakeTranslation(translation);
//
//	// ワールド行列の合成
//	matWorld = MyMathUtility::MakeIdentity();
//	matWorld *= matScale;
//	matWorld *= matRot;
//	matWorld *= matTrans;
//
//	// 親オブジェクトがあれば
//	if (parent != nullptr)
//	{
//		matWorld *= parent->matWorld;
//	}
//
//	const Mathematics::Matrix4 matView = camera->GetMatView();
//	const Mathematics::Matrix4 matProjection = camera->GetMatProjection();
//
//	// 定数バッファへデータ転送
//	ConstBufferDataB0* constMap = nullptr;
//	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
//	assert(SUCCEEDED(result));
//	constMap->mat = matWorld* matView * matProjection;
//	constBuffB0->Unmap(0, nullptr);
//}

void Object3d::Draw(WorldTransform* worldTransform)
{
	cmdList_ = DirectXCommon::GetInstance()->GetCommandList();

	// nullチェック
	assert(device_);
	assert(Object3d::cmdList_);

	// モデルの割り当てがなければ描画しない
	if (model == nullptr)
	{
		return;
	}

	// パイプラインステートの設定
	cmdList_->SetPipelineState(pip.pipelineState.Get());
	// ルートシグネチャの設定
	cmdList_->SetGraphicsRootSignature(pip.rootSignature.Get());
	// プリミティブ形状の設定コマンド
	cmdList_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 定数バッファビューをセット
	cmdList_->SetGraphicsRootConstantBufferView(2, worldTransform_->GetConstBuff()->GetGPUVirtualAddress());

	// モデル描画
	model->Draw(cmdList_.Get());
}

void Object3d::SetModel(Model* model)
{
	this->model = model;
}

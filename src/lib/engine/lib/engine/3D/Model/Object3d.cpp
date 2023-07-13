#include "Object3d.h"
#include <windows.h>

#include "DirectX12Math.h"

/// <summary>
/// 静的メンバ変数の実態
/// </summary>
Microsoft::WRL::ComPtr<ID3D12Device> Object3d::device_;
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> Object3d::cmdList_;
RootsigSetPip Object3d::pip;
Light* Object3d::light = nullptr;

void Object3d::StaticInitialize(ID3D12Device* device, int width, int height)
{
	// nullptrチェック
	assert(device);

	Object3d::device_ = device;

	// グラフィックスパイプラインの生成
	CreateGraphicsPipeline();

	ObjModel::SetDevice(device);
}

void Object3d::CreateGraphicsPipeline()
{
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト

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
	HRESULT result;

	//定数バッファの生成
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用

	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = (sizeof(ConstBufferDataB0) + 0xff) & ~0xff;//頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = device_->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));
	assert(SUCCEEDED(result));

	return true;
}

//void Object3d::Update(Camera* camera)
//{
//	HRESULT result;
//	MyMath::Matrix4 matScale, matRot, matTrans;
//
//	// スケール、回転、平行移動行列の計算
//	matScale = MyMathUtility::MakeScaling(scale);
//	matRot = MyMathUtility::MakeIdentity();
//	matRot = MyMathUtility::MakeRotation(rotation);
//	matTrans = MyMathUtility::MakeTranslation(position);
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
//	const MyMath::Matrix4 matView = camera->GetMatView();
//	const MyMath::Matrix4 matProjection = camera->GetMatProjection();
//	const MyMath::Vector3& cameraPos = camera->GetEye();
//
//	// 定数バッファへデータ転送
//	ConstBufferDataB0* constMap = nullptr;
//	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
//	assert(SUCCEEDED(result));
//	//constMap->mat = matWorld* matView * matProjection;
//	constMap->viewproj = matView * matProjection;
//	constMap->world = matWorld;
//	constMap->cameraPos = cameraPos;
//	constBuffB0->Unmap(0, nullptr);
//}

void Object3d::Draw(WorldTransform* transform)
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
	cmdList_->SetGraphicsRootConstantBufferView(2, transform->GetGpuAddress());

	//ライトの描画
	light->Draw(cmdList_.Get(), 3);
	// モデル描画
	model->Draw(cmdList_.Get());
}

void Object3d::SetModel(ObjModel* model)
{
	this->model = model;
}

void Object3d::SetLight(Light* light)
{
	Object3d::light = light;
}

void Object3d::SetPosition(MyMath::Vector3 position_)
{
	position = position_;
}

void Object3d::SetScale(MyMath::Vector3 scale_)
{
	scale = scale_;
}

void Object3d::SetRotation(MyMath::Vector3 rotation_)
{
	rotation = rotation_;
}

namespace MyMath
{
	Vector3 GetWorldPosition(Object3d& transform)
	{
		// ワールド座標を入れる変数
		Vector3 worldPos;
		// ワールド行列の平行移動成分を取得
		worldPos.x = transform.matWorld.m[3][0];
		worldPos.y = transform.matWorld.m[3][1];
		worldPos.z = transform.matWorld.m[3][2];

		return worldPos;
	}

	Matrix4 MakeWorldMatrix4(Object3d& transform)
	{
		Matrix4 matWorld = MyMathUtility::MakeIdentity();
		Matrix4 matScale, matRot, matTrans;

		// スケーリング倍率
		matScale = MyMathUtility::MakeScaling(transform.scale);
		// 回転行列
		matRot = MyMathUtility::MakeRotation(transform.rotation);
		// 移動量
		matTrans = MyMathUtility::MakeTranslation(transform.position);

		// matWorldに掛け算
		matWorld = matScale * matRot * matTrans;

		if (transform.parent)
		{
			matWorld *= transform.parent->matWorld;
		}

		return matWorld;
	}
}

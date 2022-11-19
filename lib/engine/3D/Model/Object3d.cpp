#include "Object3d.h"
#include <cassert>

void Object3d::StaticInitialize(DirectXCommon* device, WinApp* width, WinApp* height)
{
}

Object3d* Object3d::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	Object3d* object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!object3d->Initialize()) {
		delete object3d;
		assert(0);
		return nullptr;
	}

	// スケールをセット
	float scale_val = 20;
	object3d->scale = { scale_val,scale_val,scale_val };

	return object3d;
}

void Object3d::Initialize()
{
}

void Object3d::Update()
{
}

void Object3d::Draw()
{
}

void Object3d::PreDraw()
{
}

void Object3d::PostDraw()
{
}

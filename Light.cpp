#include "Light.h"
#include <cassert>

void Light::StaticInitialize(DirectXCommon* device)
{
	device_ = DirectXCommon::GetInstance();
	//再初期化チェック
	assert(!device_);
	//nullptrチェック
	assert(device);
	//静的メンバ変数セット
	device_ = device;
}

void Light::Initialize()
{
}

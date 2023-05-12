#include "Light.h"
#include <cassert>

void Light::StaticInitialize(DirectXCommon* device)
{
	device_ = DirectXCommon::GetInstance();
	//�ď������`�F�b�N
	assert(!device_);
	//nullptr�`�F�b�N
	assert(device);
	//�ÓI�����o�ϐ��Z�b�g
	device_ = device;
}

void Light::Initialize()
{
}

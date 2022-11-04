#pragma once
#include "DirectXCommon.h"

class SpriteCommon
{
public:
	void Initialize(DirectXCommon* directXCommon);

private:
	// DirectXCommon
	DirectXCommon* directXCommon_ = nullptr;
};
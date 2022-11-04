#pragma once
#include "SpriteCommon.h"

class Sprite
{
public:
	void Initialize(SpriteCommon* spriteCommon);

private:
	SpriteCommon* spriteCommon_ = nullptr;
};
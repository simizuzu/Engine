#pragma once
#include <DirectXMath.h>
#include "TextureManager.h"

class Sprite
{
public:
	void Initialize(TextureManager* textureManager);

private:
	TextureManager* textureManager_ = nullptr;
};
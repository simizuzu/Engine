#pragma once
#include <DirectXMath.h>
#include "TextureManager.h"

class Sprite
{
public:
	void Initialize(TextureManager* textureManager);
	
	void InitializeVertexBuff();

private:
	TextureManager* textureManager_ = nullptr;
};
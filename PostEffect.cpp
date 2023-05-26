#include "PostEffect.h"

PostEffect::PostEffect()
	: Sprite(
		100,
		{0,0},
		{500.0f,500.0f},
		{1,1,1,1},
		{0.0f,0.0f},
		false,
		false)
{
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
}

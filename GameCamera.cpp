#include "GameCamera.h"

void GameCamera::Initialize(Input* input)
{
	input_ = input;
	input_->GetInstance();
}

void GameCamera::Update(Camera* camera)
{
	if (input_->TriggerPushKey(DIK_RIGHT))
	{
		endPoint.x = 50;
		MyMathUtility::EaseOutQuint(startPoint.x,endPoint.x,nowFlame,endFlame);
	}
}

void GameCamera::Reset()
{
}

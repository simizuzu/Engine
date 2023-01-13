#include "DoorManager.h"

void DoorManager::Initialize(Mathematics::Vector3 vector)
{
	vector_ = vector;

	door_[0] = std::make_unique<door>();
	door_[1] = std::make_unique<door>();
	door_[2] = std::make_unique<door>();
	door_[3] = std::make_unique<door>();

	door_[0]->Initialize(Mathematics::Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z), Mathematics::Vector3(0.0f, 30.0f * MyMathUtility::degree2Radius, 0.0f));
	door_[1]->Initialize(Mathematics::Vector3(600 * vector_.x, 4.0f, 600 * -vector_.z), Mathematics::Vector3(0.0f, 330.0f * MyMathUtility::degree2Radius, 0.0f));
	door_[2]->Initialize(Mathematics::Vector3(450 * vector_.x, 4.0f, 450 * -vector_.z), Mathematics::Vector3(0.0f, 330.0f * MyMathUtility::degree2Radius, 0.0f));
	door_[3]->Initialize(Mathematics::Vector3(300 * vector_.x, 4.0f, 300 * -vector_.z), Mathematics::Vector3(0.0f, 330.0f * MyMathUtility::degree2Radius, 0.0f));

	textureHandle_ = TextureManager::Load("Resources/PushSpace.png");
	sprite_= std::make_unique<Sprite>();
	sprite_->Initialize();
}

void DoorManager::Update(int frequencyInvocationDoor)
{
	if (frequencyInvocationDoor == 1)
	{
		door_[frequencyInvocationDoor-1]->Update(Mathematics::Vector3(vector_.z,0.0f,-vector_.x));
	}
	if (frequencyInvocationDoor == 2)
	{
		door_[frequencyInvocationDoor-1]->Update(Mathematics::Vector3(vector_.z, 0.0f, vector_.x));
	}
	if (frequencyInvocationDoor == 3)
	{
		door_[frequencyInvocationDoor-1]->Update(Mathematics::Vector3(vector_.z, 0.0f, vector_.x));
	}
	if (frequencyInvocationDoor == 4)
	{
		door_[frequencyInvocationDoor-1]->Update(Mathematics::Vector3(vector_.z, 0.0f, vector_.x));
	}
}

void DoorManager::Draw(Camera* camera)
{
	for (int i = 0; i < 4; i++)
	{
		door_[i]->Draw(camera);
	}
}
void DoorManager::SpriteDraw()
{
	sprite_->DrawSprite(textureHandle_, { 640,640});
}

void DoorManager::Reset()
{
	door_[0]->Reset(Mathematics::Vector3(375 * vector_.x, 4.0f, 750 + 375 * vector_.z));
	door_[1]->Reset(Mathematics::Vector3(600 * vector_.x, 4.0f, 600 * -vector_.z));
	door_[2]->Reset(Mathematics::Vector3(450 * vector_.x, 4.0f, 450 * -vector_.z));
	door_[3]->Reset(Mathematics::Vector3(300 * vector_.x, 4.0f, 300 * -vector_.z));
}

bool DoorManager::GetMashFlag(int frequencyInvocationDoor)
{
	return door_[frequencyInvocationDoor-1]->GetMashFlag();
}

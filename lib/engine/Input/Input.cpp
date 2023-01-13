#include "Input.h"

void Input::Initialize()
{
	HRESULT result;
	WinApp* winApp = WinApp::GetInstance();

	//DirectInput�̏�����
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h������
	keyboard_ = new Keyboard();
	keyboard_->Initialize(directInput.Get());

	// �R���g���[���[������
	controller_ = new Controller();
}

void Input::Update() 
{
	// �L�[�{�[�h����
	keyboard_->Update();
	// �R���g���[���[����
	controller_->Update();
}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

#pragma region �L�[�{�[�h
unsigned char Input::GetKeyTime(int keyName)
{
	if (PushKey(keyName))
	{
		key[keyName]++;
		if (key[keyName] >= 255)
		{
			key[keyName] = 254;
		}
	}
	else
	{
		key[keyName] = 0;
	}
	return key[keyName];
}

bool Input::PushKey(BYTE keyNum) { // ���������
	return keyboard_->PushKey(keyNum);
}

bool Input::ReleaseKey(BYTE keyNum) { // ���������
	return keyboard_->ReleaseKey(keyNum);
}

bool Input::TriggerPushKey(BYTE keyNum) { // �������u��
	return keyboard_->TriggerPushKey(keyNum);
}

bool Input::TriggerReleaseKey(BYTE keyNum) { // �������u��
	return keyboard_->TriggerReleaseKey(keyNum);
}
#pragma endregion

#pragma region �R���g���[���[
bool Input::TriggerButton(ControllerButton button)
{
	return controller_->TriggerButton(button);
}
bool Input::TriggerStick(ControllerStick stickInput, const float& deadZoneRange, const Mathematics::Vector2& deadZoneInitial)
{
	return controller_->TriggerStick(stickInput,deadZoneRange,deadZoneInitial);
}
bool Input::PushButton(ControllerButton button)
{
	return controller_->PushButton(button);
}
bool Input::InputStick(ControllerStick stickInput, const float& deadZoneRange, const Mathematics::Vector2& deadZoneInitial)
{
	return controller_->InputStick(stickInput, deadZoneRange, deadZoneInitial);
}
bool Input::ReleaseTriggerButton(ControllerButton button)
{
	return controller_->ReleaseTriggerButton(button);
}
bool Input::ReleaseTriggerStick(ControllerStick stickInput, const float& deadZoneRange, const Mathematics::Vector2& deadZoneInitial)
{
	return controller_->ReleaseTriggerStick(stickInput, deadZoneRange, deadZoneInitial);
}
void Input::ShakeController(const float& power, const int& flame)
{
	controller_->ShakeController(power, flame);
}
Mathematics::Vector2 Input::GetLeftStickVec(const Mathematics::Vector2& deadZoneRange)
{
	return controller_->GetLeftStickVec(deadZoneRange);
}
Mathematics::Vector2 Input::GetRightStickVec(const Mathematics::Vector2& deadZoneRange)
{
	return controller_->GetRightStickVec(deadZoneRange);
}
#pragma endregion
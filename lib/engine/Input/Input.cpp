#include "Input.h"

void Input::Initialize()
{
	HRESULT result;
	WinApp* winApp = WinApp::GetInstance();

	//DirectInput�̏�����
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	keyboard_ = new Keyboard();
	keyboard_->Initialize(directInput.Get());
}

void Input::Update() {
	keyboard_->Update();
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
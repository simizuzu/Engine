#include "Input.h"

void Input::Initialize()
{
	HRESULT result;
	WinApp* winApp = WinApp::GetInstance();

	//DirectInput‚Ì‰Šú‰»
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	keyboard_ = new Keyboard();
	keyboard_->Initialize(directInput.Get());
}

void Input::Update() {
	keyboard_->Update();
}

bool Input::PushKey(BYTE keyNum) { // ‰Ÿ‚µ‚½ó‘Ô
	return keyboard_->PushKey(keyNum);
}

bool Input::ReleaseKey(BYTE keyNum) { // —£‚µ‚½ó‘Ô
	return keyboard_->ReleaseKey(keyNum);
}

bool Input::TriggerPushKey(BYTE keyNum) { // ‰Ÿ‚µ‚½uŠÔ
	return keyboard_->TriggerPushKey(keyNum);
}

bool Input::TriggerReleaseKey(BYTE keyNum) { // —£‚µ‚½uŠÔ
	return keyboard_->TriggerReleaseKey(keyNum);
}
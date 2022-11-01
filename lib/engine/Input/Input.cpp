#include "Input.h"

void Input::Initialize()
{
	HRESULT result;
	WinApp* winApp = WinApp::GetInstance();

	//DirectInputの初期化
	result = DirectInput8Create(winApp->GetHinstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// キーボード初期化
	keyboard_ = new Keyboard();
	keyboard_->Initialize(directInput.Get());
}

void Input::Update() 
{
	// キーボード処理
	keyboard_->Update();
}

bool Input::PushKey(BYTE keyNum) { // 押した状態
	return keyboard_->PushKey(keyNum);
}

bool Input::ReleaseKey(BYTE keyNum) { // 離した状態
	return keyboard_->ReleaseKey(keyNum);
}

bool Input::TriggerPushKey(BYTE keyNum) { // 押した瞬間
	return keyboard_->TriggerPushKey(keyNum);
}

bool Input::TriggerReleaseKey(BYTE keyNum) { // 離した瞬間
	return keyboard_->TriggerReleaseKey(keyNum);
}
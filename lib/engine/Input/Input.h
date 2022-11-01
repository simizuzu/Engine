#pragma once
#include <memory>
#include "Keyboard.h"
//
//#include <wrl.h>
//#include <cassert>

using namespace DirectX;

class Input
{
private:
	// テンプレート
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	ComPtr<IDirectInput8> directInput;
	Keyboard* keyboard_ = nullptr;;
public:
	void Initialize();
	void Update();
	bool PushKey(BYTE keyNum);
	bool ReleaseKey(BYTE keyNum);
	bool TriggerPushKey(BYTE keyNum);
	bool TriggerReleaseKey(BYTE keyNum);

private:

	BYTE oldkey[256] = {};
	BYTE key[256] = {};
};


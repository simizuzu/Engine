#pragma once

#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include <DirectXMath.h>
#include <array>
#include <wrl.h>
#include <cassert>
#include "WinApp.h"

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;

class Keyboard
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	void Initialize(IDirectInput8* directInput);
	void Update();
	bool PushKey(BYTE keyNum);
	bool ReleaseKey(BYTE keyNum);
	bool TriggerPushKey(BYTE keyNum);
	bool TriggerReleaseKey(BYTE keyNum);

private:

	WinApp* winApp_ = nullptr;

	ComPtr<IDirectInputDevice8> keyboard;

	BYTE oldkey[256] = {};
	BYTE key[256] = {};
};


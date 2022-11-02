#pragma once

#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
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
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="directInput">:DirectInput�I�u�W�F�N�g</param>
	void Initialize(IDirectInput8* directInput);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �L�[����������Ԃ̏���
	/// </summary>
	/// <param name="keyNum">:�L�[�i���o�[</param>
	/// <returns>�L�[�i���o�[</returns>
	bool PushKey(BYTE keyNum);
	/// <summary>
	/// �L�[�𗣂�����Ԃ̏���
	/// </summary>
	/// <param name="keyNum">:�L�[�i���o�[</param>
	/// <returns>�L�[�i���o�[</returns>
	bool ReleaseKey(BYTE keyNum);
	/// <summary>
	/// �L�[���������u�Ԃ̏���
	/// </summary>
	/// <param name="keyNum">:�L�[�i���o�[</param>
	/// <returns>�L�[�i���o�[</returns>
	bool TriggerPushKey(BYTE keyNum);
	/// <summary>
	/// �L�[�𗣂����u�Ԃ̏���
	/// </summary>
	/// <param name="keyNum">:�L�[�i���o�[</param>
	/// <returns>�L�[�i���o�[</returns>
	bool TriggerReleaseKey(BYTE keyNum);

private:

	WinApp* winApp_ = nullptr;

	ComPtr<IDirectInputDevice8> keyboard;

	BYTE oldkey[256] = {};
	BYTE key[256] = {};
};

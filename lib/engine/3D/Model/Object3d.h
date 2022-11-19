#pragma once

#include <windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

#include "DirectX12Math.h"
#include "DirectXCommon.h"
#include "WinApp.h"



class Object3d
{
private: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �ÓI�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">: �f�o�C�X</param>
	/// <param name="width">: ��</param>
	/// <param name="height">: �c</param>
	static void StaticInitialize(DirectXCommon* device,WinApp* width, WinApp* height);

	static Object3d* Create();

	/// <summary>
	/// �`��O����
	/// </summary>
	static void PreDraw();

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �N���X�Ăяo��
	DirectXCommon* dxCommon_ = nullptr;
};
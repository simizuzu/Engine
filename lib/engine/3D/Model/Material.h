#pragma once
#include <d3d12.h>
#include <wrl.h>
#include <string>

#include "DirectXCommon.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

struct ConstBufferData
{
	Mathematics::Vector3 ambient;
};

class Material
{
private: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(DirectXCommon* device);

	/// <summary>
	/// �}�e���A������
	/// </summary>
	/// <returns>�������ꂽ�}�e���A��</returns>
	static Material* Create();
};
#pragma once

#include "TextureManager.h"

class Shader
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	// �X�v���C�g�p
	void CreateSpriteShade(ComPtr<ID3DBlob>& vsBlob, ComPtr<ID3DBlob>& psBlob);
	// 3D�I�u�W�F�N�g�p
	void CreateObjShade(ComPtr<ID3DBlob>& vsBlob, ComPtr<ID3DBlob>& psBlob);


};
#pragma once

#include "TextureManager.h"

class Shader
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // �����o�ϐ�
	// ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> vsBlob;
	// �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob;
	// �G���[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob;

public: // �����o�֐�
	void CreateSpriteShade();

};
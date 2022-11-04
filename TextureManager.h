#pragma once

#include <d3d12.h>
#include <wrl.h>

/// <summary>
/// �e�N�X�`���}�l�[�W��
/// </summary>
class TextureManager
{
public: // �G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �萔
	static const int MaxSRVCount = 512; // �e�N�X�`���̍ő喇��

public: // �����o�֐�
	void Initialize();

private: // �����o�ϐ�
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	ComPtr<ID3D12Resource> spriteTexBuff[MaxSRVCount];
};


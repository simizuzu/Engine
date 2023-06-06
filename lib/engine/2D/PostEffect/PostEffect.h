#pragma once
#include <DirectXMath.h>
#include <memory>
#include <wrl.h>
#include <d3dx12.h>

#include "DirectX12Math.h"
#include "TextureManager.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#include "Sprite.h"
#include "TextureManager.h"

class PostEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

	void Initialize();

	/// <summary>
	/// �`��R�}���h�̎��s
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	/// <summary>
	/// �e�N�X�`������
	/// </summary>
	void CreateTextureBuff();

	/// <summary>
	/// SRV�쐬
	/// </summary>
	void CreateSRVDesc();

	/// <summary>
	/// RTV�쐬
	/// </summary>
	void CreateRTVDesc();

	/// <summary>
	/// DSV�쐬
	/// </summary>
	void CreateDSVDesc();

	/// <summary>
	/// �[�x�o�b�t�@����
	/// </summary>
	void CreateDepthBuff();

private:
	//�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	//�e�N�X�`���o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	//SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//RTV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//DSV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;


	WinApp* winApp_ = nullptr;
};


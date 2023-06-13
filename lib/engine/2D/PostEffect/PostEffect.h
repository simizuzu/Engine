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
#include "DirectXCommon.h"

struct VertexPosUv
{
	Mathematics::Vector3 pos;
	Mathematics::Vector2 uv;
};

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

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList, WinApp* winApp);

	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

private:
	/// <summary>
	/// ���_�f�[�^�̐���
	/// </summary>
	void CreateVertexData(ID3D12Device* device);

	/// <summary>
	/// �e�N�X�`������
	/// </summary>
	void CreateTextureBuff(ID3D12Device* device, WinApp* winApp);

	/// <summary>
	/// SRV�쐬
	/// </summary>
	void CreateSRVDesc(ID3D12Device* device);

	/// <summary>
	/// RTV�쐬
	/// </summary>
	void CreateRTVDesc(ID3D12Device* device);

	/// <summary>
	/// DSV�쐬
	/// </summary>
	void CreateDSVDesc(ID3D12Device* device, WinApp* winApp);

	/// <summary>
	/// �[�x�o�b�t�@����
	/// </summary>
	void CreateDepthBuff(ID3D12Device* device);

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
	//���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> vertBuff;
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	static const float clearColor[4];

	std::shared_ptr<WinApp> winApp_;
	std::shared_ptr<DirectXCommon> dxCommon;
};


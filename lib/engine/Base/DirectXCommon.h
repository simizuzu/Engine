#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <vector>
#include <dxgi1_6.h>

#include "WinApp.h"

class DirectXCommon
{
private:
	// DirectX ����������
	HRESULT result;
	ID3D12Device* device = nullptr;
	IDXGIFactory7* dxgiFactory = nullptr;
	IDXGISwapChain4* swapChain = nullptr;
	ID3D12CommandAllocator* cmdAllocator = nullptr;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	ID3D12DescriptorHeap* rtvHeap = nullptr;


	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{}; // �O�ɏo���Ȃ���G���[�N����
	// �X���b�v�`�F�[���̐ݒ�
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	// �o�b�N�o�b�t�@
	std::vector<ID3D12Resource*> backBuffers;

	// �t�F���X�̐���
	ID3D12Fence* fence = nullptr;
	UINT64 fenceVal = 0;

	//�o���A�[�f�X�N
	D3D12_RESOURCE_BARRIER barrierDesc{};

	FLOAT clearColor[4] = { 0.1f,0.25f, 0.5f,0.0f }; // ���ΐF


	//DXGI�܂�菉����
	void InitializeDXGI();

	//�ŏI�I�ȃ����_�[�^�[�Q�b�g�̐���
	void CreatRtv();

	//�X���b�v�`�F�C���̐���
	void CreateSwapChain();

	//�R�}���h�܂�菉����
	void InitializeCommand();

	//�t�F���X����
	void CreateFence();

	//�f�o�b�O���C���[��L���ɂ���
	void EnableDebugLayer();


public:
	static DirectXCommon* GetInstance();

	// DirectX���t���[��������������
	void Initialize();
	void PreDraw();
	void PostDraw();
	void ExecuteCommand();
	// DirectX���t���[�����������܂�

	// �Z�b�^�[
	//�w�i�F�ύX(RGBA)
	void SetBackScreenColor(float red, float green, float blue, float alpha);

	// �Q�b�^�[
	ID3D12Device* GetDevice();
	IDXGIFactory7* GetDxgiFactory();
	IDXGISwapChain4* GetSwapChain();
	ID3D12CommandAllocator* GetCmdAllocator();
	ID3D12GraphicsCommandList* GetCommandList();
	ID3D12CommandQueue* GetCommandQueue();
	ID3D12DescriptorHeap* GetRtvHeap();
	ID3D12Fence* GetFence();
	UINT64 GetFenceVal();
};

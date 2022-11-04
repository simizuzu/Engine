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
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	std::vector< Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{}; // �O�ɏo���Ȃ���G���[�N����
	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	// �t�F���X�̐���
	UINT64 fenceVal = 0;
	//�o���A�[�f�X�N
	D3D12_RESOURCE_BARRIER barrierDesc{};
	// �w�i�F
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
	void BreakOnSeverity();

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

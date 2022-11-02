#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <cassert>
#include <vector>

#include "WinApp.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

class DirectXCommon
{
private:
	// �e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	HRESULT result;
	ComPtr<ID3D12Device> device;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	// �o�b�N�o�b�t�@
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// �[�x�e�X�g�̐ݒ�
	ID3D12Resource* depthBuff = nullptr;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
	// �t�F���X�̐���
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	// ���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc{};
	// ��ʂ�h��Ԃ��F
	FLOAT clearColor[4] = { 0.1f,0.25f,0.5f,0.0f };
public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �`��O����
	/// </summary>
	void PreDraw();
	/// <summary>
	/// �`��㏈��
	/// </summary>
	void PostDraw();

	// �Q�b�^�[
	ID3D12Device* GetDevice();
	IDXGIFactory7* GetDxgiFactory();
	IDXGISwapChain4* GetSwapChain();
	ID3D12CommandAllocator* GetCmdAllocator();
	ID3D12GraphicsCommandList* GetCommandList();
	ID3D12CommandQueue* GetCommandQueue();
	ID3D12DescriptorHeap* GetRtvHeap();
	ID3D12Fence* GetFence();

	void SetBackScreenColor(float red, float green, float blue, float alpha);
private: // �e������
	/// <summary>
	/// �f�o�C�X�̏�����
	/// </summary>
	void InitializeDevice();
	/// <summary>
	/// �R�}���h�֘A�̏�����
	/// </summary>
	void InitializeCommand();
	/// <summary>
	/// �X���b�v�`�F�[���̏�����
	/// </summary>
	void InitializeSwapChain();
	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̏�����
	/// </summary>
	void InitializeRTV();
	/// <summary>
	/// �[�x�o�b�t�@�̏�����
	/// </summary>
	void InitializeDepthBuffer();
	/// <summary>
	/// �t�F���X�̏�����
	/// </summary>
	void InitializeFence();
	/// <summary>
	/// �R�}���h�̃t���b�V��
	/// </summary>
	void ExecuteCommand();

private: // �G���[���b�Z�[�W�̗}��
	/// <summary>
	/// �f�o�b�O���C���[��L���ɂ���
	/// </summary>
	void EnableDebugLayer();
	/// <summary>
	/// �f�o�b�N���C���[���Ɏ~�߂鏈��(Windows10��)
	/// </summary>
	void BreakOnSeverity();

private:
	WinApp* winApp = nullptr;
};


#include "DirectXCommon.h"

void DirectXCommon::Initialize(WinApp* winApp)
{
	// NULL���o
	assert(winApp);
	// �����o�ϐ��ɋL�^
	this->winApp = winApp;

#ifdef _DEBUG
	EnableDebugLayer();
#endif

	// �f�o�C�X�̐���
	InitializeDevice();
	BreakOnSeverity();
	// �R�}���h�֘A�̏�����
	InitializeCommand();
	// �X���b�v�`�F�[���̏�����
	InitializeSwapChain();
	// �����_�[�^�[�Q�b�g�r���[�̏�����
	InitializeRTV();
	// �t�F���X�̏�����
	InitializeFence();
}

#pragma region �e������
void DirectXCommon::InitializeDevice()
{
	// �Ή����x���̔z��
	D3D_FEATURE_LEVEL levels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	// DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	// �A�_�v�^�[�̗񋓗p
	std::vector <ComPtr<IDXGIAdapter4>>adapters;
	// �����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr<IDXGIAdapter4> tmpAdapter;

	// �p�t�H�[�}���X���������̂��珇�ɁA���ׂẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference(i,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
		i++) {
		//���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}

	// �Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		// �A�_�v�^�[�̏����擾����
		adapters[i]->GetDesc3(&adapterDesc);

		// �\�t�g�E�F�A�f�o�C�X�����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			// �f�o�C�X���̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i];
			break;
		}
	}

	// Direct3D�f�o�C�X�̏�����
	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		// �̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&device));
		if (result == S_OK) {
			// �f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}
	}
}

void DirectXCommon::InitializeCommand()
{
	// �R�}���h�A���P�[�^�̐���
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));

	// �R�}���h���X�g�𐶐�
	result = device->CreateCommandList(0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(), nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));

	// �R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{}; //�\���̂̒��g��0�ŃN���A���Ă���
	// �R�}���h�L���[�𐶐�
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeSwapChain()
{
	ComPtr<IDXGISwapChain1> swapChain1;

	// �X���b�v�`�F�[���̐ݒ�
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// �X���b�v�`�F�[������
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(), 
		winApp->GetHwnd(),
		&swapChainDesc, 
		nullptr, 
		nullptr, 
		&swapChain1);

	assert(SUCCEEDED(result));

	// ��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	swapChain1.As(&swapChain);
}

void DirectXCommon::InitializeRTV()
{
	//�f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; //�����_�[�^�[�Q�b�g�r���[
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;
	//�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	//�o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//�X���b�v�`�F�[������o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//�f�X�N���v�^�q�|�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//�����\���ŃA�h���X�������
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�����_�[�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}

void DirectXCommon::InitializeFence()
{
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}
#pragma endregion

void DirectXCommon::PreDraw()
{
	// �o�b�N�o�b�t�@�̔ԍ����擾�i2�Ȃ̂�0�Ԃ�1�ԁj
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	// ���\�[�X�o���A�ŏ������݉\�ɕύX
	D3D12_RESOURCE_BARRIER barrierDesc{};
	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get();//�o�b�N�o�b�t�@���w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;//�\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;//�`���Ԃ�
	commandList->ResourceBarrier(1, &barrierDesc);

	// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
	rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	commandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);

	// ��ʂ̐F��ύX
	commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
}
void DirectXCommon::PostDraw()
{
}

#pragma region �G���[���b�Z�[�W�̗}��
void DirectXCommon::EnableDebugLayer()
{
	//�f�o�b�N���C���[���I����
	ComPtr<ID3D12Debug1> debugController;

	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
}

void DirectXCommon::BreakOnSeverity()
{
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);	// �s����(�G���[����)�Ɏ~�܂�
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);		// �G���[���Ɏ~�܂�
		infoQueue->Release();
	}

	// �}������G���[
	D3D12_MESSAGE_ID denyIds[] = {
		/*
		 * Windows11�ł�DXGI�f�o�b�N���C���[��D12�f�o�b�N���C���[�̑��ݍ�p�o�O�ɂ��G���[���b�Z�[�W
		 * https://stackoverflow.com/questions/69805245/directx-12-application-is-crashing-in-windows-11
		 */
		D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
	};
	// �}������\�����x��
	D3D12_MESSAGE_SEVERITY severiries[] = { D3D12_MESSAGE_SEVERITY_INFO };
	D3D12_INFO_QUEUE_FILTER filter{};
	filter.DenyList.NumIDs = _countof(denyIds);
	filter.DenyList.pIDList = denyIds;
	filter.DenyList.NumSeverities = _countof(severiries);
	filter.DenyList.pSeverityList = severiries;
	// �w�肵���G���[�̕\����}������
	infoQueue->PushStorageFilter(&filter);
}
#pragma endregion

#pragma region �Q�b�^�[
ID3D12Device* DirectXCommon::GetDevice()
{
	return device.Get();
}

IDXGIFactory7* DirectXCommon::GetDxgiFactory()
{
	return dxgiFactory.Get();
}

IDXGISwapChain4* DirectXCommon::GetSwapChain()
{
	return swapChain.Get();
}

ID3D12CommandAllocator* DirectXCommon::GetCmdAllocator()
{
	return commandAllocator.Get();
}

ID3D12GraphicsCommandList* DirectXCommon::GetCommandList()
{
	return commandList.Get();
}

ID3D12CommandQueue* DirectXCommon::GetCommandQueue()
{
	return commandQueue.Get();
}

ID3D12DescriptorHeap* DirectXCommon::GetRtvHeap()
{
	return rtvHeap.Get();
}

ID3D12Fence* DirectXCommon::GetFence()
{
	return fence.Get();
}
#pragma endregion
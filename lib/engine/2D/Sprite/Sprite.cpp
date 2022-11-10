#include "Sprite.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;

void Sprite::Initialize(TextureManager* textureManager)
{
	textureManager_ = textureManager;

	InitializeVertexBuff();
	InitializeShadeLoad();
}

void Sprite::Update()
{
	
}

void Sprite::Draw()
{
}

void Sprite::InitializeVertexBuff()
{
	// ���_�f�[�^
	XMFLOAT3 vertices[] = {
		{-0.5f, -0.5f, 0.0f}, // ����
		{-0.5f, +0.5f, 0.0f}, // ����
		{+0.5f, -0.5f, 0.0f}, // �E��
	};
	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};		// �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	// GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	HRESULT result = dxCommon_->GetInstance()->GetDevice()->CreateCommittedResource(
		&heapProp,	// �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,	// ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);
	assert(SUCCEEDED(result));

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	XMFLOAT3* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	// ���W���R�s�[
	}
	// �Ȃ��������
	vertBuff->Unmap(0, nullptr);

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(XMFLOAT3);
}

void Sprite::InitializeShadeLoad()
{
	dxCommon_ = DirectXCommon::GetInstance();
#pragma region �V�F�[�_�ǂݍ���
	//�@���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	HRESULT result = D3DCompileFromFile(
		L"Resources/shaders/SpriteVS.hlsl",	// �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// �C���N���[�h�\�ɂ���
		"main", "vs_5_0",	// �G���g���[�|�C���g���A�V�F�[�_���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�N�p�ݒ�
		0,&vsBlob, &errorBlob
	);

	// �V�F�[�_�̃G���[���e��\��
	if (FAILED(result)) 
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/shaders/SpritePS.hlsl",	// �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// �C���N���[�h�\�ɂ���
		"main", "ps_5_0",	// �G���h���[�|�C���g���A�V�F�[�_���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�N�p�ݒ�
		0, &psBlob, &errorBlob
	);

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}
#pragma endregion
#pragma region ���_���C�A�E�g
	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
	};
#pragma endregion
#pragma region �O���t�B�b�N�X�p�C�v���C��
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// ���_�V�F�[�_�A�s�N�Z���V�F�[�_���p�C�v���C���ɐݒ�
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();
	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�
	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	// �J�����O���Ȃ�
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;	// �O�ʃJ�����O
	//pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	// �w�ʃJ�����O
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	// �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true;			// �[�x�N���b�s���O��L����
	// �u�����h�X�e�[�g
	pipelineDesc.BlendState.RenderTarget[0].RenderTargetWriteMask
		= D3D12_COLOR_WRITE_ENABLE_ALL;		// RGBA�S�Ẵ`�����l����`��
	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE; // �O�p�`
	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0~255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
		&rootSigBlob, &errorBlob);
	assert(SUCCEEDED(result));
	result = dxCommon_->GetDevice()->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
		IID_PPV_ARGS(&rootsignature));
	assert(SUCCEEDED(result));
	rootSigBlob->Release();
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = rootsignature.Get();

	// �p�C�v���C���X�e�[�g�̐���
	result = dxCommon_->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));
	assert(SUCCEEDED(result));
#pragma endregion
	
}
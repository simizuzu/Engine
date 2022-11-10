#include "Material.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

void Material::Initialize()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectXCommon::GetInstance()->GetDevice();

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g

	bool vsflag = false;
	bool psflag = false;

	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

#pragma region ���_�V�F�[�_�[

	//���_�V�F�[�_�[
	if (vsFiledata.pFileName.size() > 4)
	{
		// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		result = D3DCompileFromFile(
			vsFiledata.pFileName.c_str(), // �V�F�[�_�t�@�C����
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
			vsFiledata.pEntrypoint.c_str(), vsFiledata.pTarget.c_str(), // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
			0,
			&vsBlob, &errorBlob);

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

		vsflag = true;
	}

#pragma endregion

#pragma region �s�N�Z���V�F�[�_�[

	//�s�N�Z���V�F�[�_�|
	if (psFiledata.pFileName.size() > 4)
	{
		// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
		result = D3DCompileFromFile(
			psFiledata.pFileName.c_str(), // �V�F�[�_�t�@�C����
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
			psFiledata.pEntrypoint.c_str(), psFiledata.pTarget.c_str(), // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
			D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
			0,
			&psBlob, &errorBlob);

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
		};

		psflag = true;
	}

#pragma endregion
}
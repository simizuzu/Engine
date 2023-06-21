#pragma once
#include <wrl.h>

#include "WinApp.h"
#include "DirectXCommon.h"

class ImGuiManager final
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	/// <summary>
	/// ImGui��t�J�n
	/// </summary>
	void Begin();
	
	/// <summary>
	/// ImGui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// ��ʂւ̕`��
	/// </summary>
	void Draw(DirectXCommon* dxCommon);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	// �V���O���g��
	static ImGuiManager* GetInstance();

private:
	// SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

private:
	ImGuiManager() = default;
	~ImGuiManager() = default;
	ImGuiManager& operator=(const ImGuiManager&) = delete;
	ImGuiManager(const ImGuiManager&) = delete;
};
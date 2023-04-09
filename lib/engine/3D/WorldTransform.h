#pragma once
#include "AvoidWarning.h"
#include "Camera.h"
#include "EngineUtility.h"

class WorldTransform
{

public:
	//������
	void Initialize();
	//�X�V
	void Update(Camera* camera,bool billboradFlag = false);

	//�Q�b�^�[
	D3D12_GPU_VIRTUAL_ADDRESS GetGpuAddress();

private: //�����o�֐�
	//�萔�o�b�t�@����
	void CreateConstBuffer();

private:
	//�萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuffer_;
	WorldvViewProCamera constBuffMap;

public:
	//���[�J�����W
	Mathematics::Vector3 translation_ = { 0.0f,0.0f,0.0f };
	//X,Y,Z�����̃��[�J����]�p
	Mathematics::Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	//���[�J���X�P�[��
	Mathematics::Vector3 scale_ = { 1.0f,1.0f,1.0f };

	Mathematics::Matrix4 matWorld;

	const WorldTransform* parent = nullptr;
};


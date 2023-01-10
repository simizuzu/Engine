//#pragma once
//
//#include <cassert>
//#include "DirectXCommon.h"
//#include "Vector3.h"
//#include "Matrix4.h"
//#include "Camera.h"
//
//class WorldTransform
//{
//public: // �����o�֐�
//	/// <summary>
//	/// ������
//	/// </summary>
//	void Initialize();
//
//	/// <summary>
//	/// ���[���h�s��̍���
//	/// </summary>
//	/// <param name="camera"></param>
//	void Update();
//
//	/// <summary>
//	/// �萔�o�b�t�@�̐���
//	/// </summary>
//	void CreateConstBuff();
//
//	/// <summary>
//	/// �s���]������
//	/// </summary>
//	void TransferMatrix(Camera* camera);
//
//public: // setter
//	void SetTranslation(Mathematics::Vector3 translation);
//	void SetScale(Mathematics::Vector3 scale);
//	void SetRotation(Mathematics::Vector3 rotation);
//
//public: // getter
//	ID3D12Resource* GetConstBuff();
//
//private:
//	// �萔�o�b�t�@
//	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
//	// �}�b�s���O�ς݃A�h���X
//	ConstBufferDataViewProjection* constMap_ = nullptr;
//
//	//�������p�̃r���[�s��v�Z
//	static Mathematics::Matrix4 defaultViewMat;
//	//�������p�̃v���W�F�N�V�����s��v�Z
//	static Mathematics::Matrix4 defaultProjectionMat;
//
//public:
//	// ���[�J���X�P�[��
//	Mathematics::Vector3 scale_ = { 1, 1, 1 };
//	// X,Y,Z�����̃��[�J����]�p
//	Mathematics::Vector3 rotation_ = { 0, 0, 0 };
//	// ���[�J�����W
//	Mathematics::Vector3 translation_ = { 0, 0, 0 };
//	// ���[�J�� �� ���[���h�ϊ��s��
//	Mathematics::Matrix4 matWorld_;
//	// �e�ƂȂ郏�[���h�ϊ��ւ̃|�C���^
//	const WorldTransform* parent_ = nullptr;
//
//	// �f�o�C�X
//	DirectXCommon* device_ = nullptr;
//};
#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"


class GameScene
{
public: // �����o�֐�
	// �R���X�g���N�^
	GameScene() = default;
	// �f�X�g���N�^
	~GameScene() = default;
	//�@������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();


private: // �����o�ϐ�
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
private:

};


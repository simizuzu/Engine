#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "GameCollisionManager.h"

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
	AudioManager* audioManager_ = nullptr;

	//�錾
	INT32 sceneNum = 0;
	char PADING[4]{};

	float pos[2] = {100,100};
private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


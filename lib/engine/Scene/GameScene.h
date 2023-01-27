#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"
#include "BaseScene.h"
#include "TextureManager.h"
#include "SceneManager.h"

#include "GameCollisionManager.h"

class GameScene : public BaseScene
{
public: // �����o�֐�
	// �R���X�g���N�^
	GameScene() = default;
	// �f�X�g���N�^
	~GameScene() = default;

	//�@������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// �I������
	void Finalize() override;


private: // �����o�ϐ�
	Input* input_ = nullptr;
	std::unique_ptr<Camera> camera;
	DirectXCommon* dxCommon_ = nullptr;
	AudioManager* audioManager_ = nullptr;

	TextureData tex;
	std::unique_ptr<Sprite> sprite_;

	//�錾
	INT32 sceneNum = 0;
	char PADING[4]{};

	// ImGui�f�o�b�N�p
	float pos[2] = {100,100};

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


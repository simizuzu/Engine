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
#include "TitleScene.h"

#include "GameCollisionManager.h"

class GameScene : public BaseScene
{
public: // �����o�֐�
	GameScene() = default;
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

	SceneManager* sceneManager_ = nullptr;

	std::unique_ptr<Object3d> tyoinoriObj;
	std::unique_ptr<Model> tyoinori;

	//�錾
	INT32 sceneNum = 0;
	char PADING[4]{};

	// ImGui�f�o�b�N�p
	Mathematics::Vector2 pos = {100,100};
	Mathematics::Vector3 posObj = { 0,0,0 };
	
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	// �T�E���h
	uint32_t gameHandle_ = 0;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜

	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};

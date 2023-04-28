#pragma once
#include <memory>
#include <map>

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

#include "LevelLoader.h"

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

	std::unique_ptr<Object3d> objCylinder;
	std::unique_ptr<Object3d> objCube;
	std::unique_ptr<Model> cylinder;
	std::unique_ptr<Model> cube;

	//�錾
	INT32 sceneNum = 0;
	char PADING[4]{};

	// ImGui�f�o�b�N�p
	Mathematics::Vector2 pos = {100,100};
	
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	LevelData* levelData = nullptr;
	std::map<std::string, Model*> models;

	// �T�E���h
	uint32_t gameHandle_ = 0;
	std::vector<Object3d*> objects;

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜

	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};


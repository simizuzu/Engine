#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "Player.h"

class GameScene
{
public: // �G�C���A�X�e���v���[�g
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	// �R���X�g���N�^
	GameScene();
	// �f�X�g���N�^
	~GameScene();
	//�@������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();

public: // �����o�֐�

private: // �����o�ϐ�
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Object3d* object3d_ = nullptr;
	std::unique_ptr<Camera> camera_;

	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
	std::unique_ptr<Model> model_;

	std::unique_ptr<Player> player_;
	std::unique_ptr<Model> playerModel_;


	// �T�E���h
	uint32_t gameHandle = 0;

	// �V�[��

	enum Scene {
		title,
		appear,
		game,
		defeat,
		gameover,
		clear
	};

	//�V�[��
	Scene scene = title;
};


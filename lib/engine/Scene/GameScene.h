#pragma once
#include <memory>

#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Object3d.h"
#include "Model.h"
#include "AudioManager.h"

#include "skydome.h"


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


private: // �N���X�ǂݍ���
	Input* input_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	std::unique_ptr<Camera> camera_;

	std::unique_ptr<skydome> skydome_;

	TextureData titleTex_;
	std::unique_ptr<Sprite> titleSprite_;

	uint16_t scene = 0;
private:

};


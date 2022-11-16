#pragma once
#include "Sprite.h"
#include <memory>

class GameScene
{
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
	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
};


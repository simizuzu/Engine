#pragma once
#include <memory>

#include "Camera.h"
#include "Sprite.h"

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
	std::unique_ptr<Sprite> sprite_;
	TextureData tex;
};


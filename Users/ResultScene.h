#pragma once
#include"Sprite2D.h"

class ResultScene
{
private:

	std::unique_ptr<Sprite2D> spriteSpace_[3];
	TextureData spaceTextureData_[3];
	Transform spaceTransform[3];

public:

	ResultScene() = default;
	~ResultScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void SpriteDraw();

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	ResultScene& operator=(const ResultScene&) = delete;
	ResultScene(const ResultScene&) = delete;
};


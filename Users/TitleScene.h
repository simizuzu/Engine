#pragma once
#include"Sprite2D.h"
#include "TextureManager.h"

class TitleScene
{
public:
	TitleScene() = default;
	~TitleScene() = default;
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void SpriteDraw();
private:
	std::unique_ptr<Sprite2D> sprite_;
	Transform transform_;
	TextureData textureHandle_;

	TextureData spaceTextureHandle_;
	std::unique_ptr<Sprite2D> spriteSpace_;
	Transform spaceTransform_;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	TitleScene& operator=(const TitleScene&) = delete;
	TitleScene(const TitleScene&) = delete;
};


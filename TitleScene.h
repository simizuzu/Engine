#pragma once
#include "BaseScene.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Input.h"
#include "GameScene.h"
#include "SceneManager.h"

// �^�C�g���V�[��
class TitleScene : public BaseScene
{
public: // �����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize() override;

private:
	Input* input = nullptr;
	SceneManager* sceneManager_= nullptr;
	TextureData tex;
	std::unique_ptr<Sprite> sprite_;
};


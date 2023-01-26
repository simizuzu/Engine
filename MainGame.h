#pragma once

#include "TextureManager.h"
#include "ImGuiManager.h"
#include "GameScene.h"
#include "Object3d.h"
#include "Framework.h"

// �Q�[���S��
class MainGame : public Framework
{
public: // �����o�֐�
	MainGame() = default;
	~MainGame() = default;

	// ������
	void Initialize() override;
	// �I��
	void Finalize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �Q�[���I���t���O
	bool endRequest_ = false;

	TextureManager* textureManager_ = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	std::unique_ptr<GameScene> gameScene;
};


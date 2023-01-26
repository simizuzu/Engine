#pragma once
#include "Input.h"
#include "WinApp.h"
#include "FPS.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ImGuiManager.h"
#include "GameScene.h"
#include "Sprite.h"
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

	Sprite* sprite_ = nullptr;
	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	FPS* fps_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	AudioManager* audioManager = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	std::unique_ptr<GameScene> gameScene;
};


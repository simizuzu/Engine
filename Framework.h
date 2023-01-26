#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "FPS.h"
#include "Sprite.h"
#include "AudioManager.h"
#include "TextureManager.h"
#include "ImGuiManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "BaseScene.h"

// �Q�[���S��
class Framework
{
public: // �����o�֐�
	virtual ~Framework() = default;
	// ������
	virtual void Initialize();
	// �X�V
	virtual void Finalize();
	// ���t���[���X�V
	virtual void Update();
	// �`��
	virtual void Draw() = 0;
	// �I���`�F�b�N
	virtual bool IsEndRequest();

	// ���s
	void Run();

protected:
	// �Q�[���I���t���O
	bool endRequest_ = false;

	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Sprite* sprite_ = nullptr;
	AudioManager* audioManager = nullptr;
	Input* input_ = nullptr;
	FPS* fps_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	std::unique_ptr<GameScene> gameScene;
	std::unique_ptr<TitleScene> titleScene;
	ImGuiManager* imGuiManager = nullptr;

	std::unique_ptr < BaseScene> baseScene;
};


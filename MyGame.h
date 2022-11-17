#pragma once

#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Input.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "GameScene.h"

class MyGame
{
public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	WinApp* winApp_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	FPS* fps_ = nullptr;
	Input* input_ = nullptr;
	TextureManager* textureManager_ = nullptr;
	std::unique_ptr<GameScene> gameScene = nullptr;
};


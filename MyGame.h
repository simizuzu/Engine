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

};


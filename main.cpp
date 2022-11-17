#include <Windows.h>
#include <memory>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "GameScene.h"

#include "MyGame.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region ��ՃV�X�e���̏�����

	MyGame game;
	game.Initialize();

#pragma endregion

#pragma region �Q�[�����[�v
	

		game.Draw();
		game.Update();

#pragma endregion

#pragma region ��ՃV�X�e���̏I��
	// �X�v���C�g���

	game.Finalize();
#pragma endregion

	return 0;
}
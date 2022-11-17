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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){
#pragma region 基盤システムの初期化

	MyGame game;
	game.Initialize();

#pragma endregion

#pragma region ゲームループ
	

		game.Draw();
		game.Update();

#pragma endregion

#pragma region 基盤システムの終了
	// スプライト解放

	game.Finalize();
#pragma endregion

	return 0;
}
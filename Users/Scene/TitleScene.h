#pragma once
#include "BaseScene.h"
#include "TextureManager.h"

#include "Input.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Camera.h"

#include "Sprite.h"
#include "Object3d.h"

// タイトルシーン
class TitleScene : public BaseScene
{
public: // メンバ関数

	TitleScene() = default;
	~TitleScene() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

private:
	Input* input_ = nullptr;
	std::unique_ptr<Camera> camera;
	SceneManager* sceneManager_= nullptr;
	TextureData tex;
	std::unique_ptr<Sprite> sprite_;

	std::unique_ptr<Object3d> tyoinoriObj;
	std::unique_ptr<Model> tyoinori;

	//ImGuiデバッグ用
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	Mathematics::Vector2 pos = { 0,0 };
};


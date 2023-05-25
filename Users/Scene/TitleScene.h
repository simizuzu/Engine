#pragma once
#include "BaseScene.h"
#include "TextureManager.h"

#include "Input.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Light.h"

#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "WorldTransform.h"

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
	std::unique_ptr<Light> light;
	SceneManager* sceneManager_= nullptr;
#pragma region Sprite
	TextureData tex;
	std::unique_ptr<Sprite> sprite_;

	TextureData tex2;
	std::unique_ptr<Sprite> warningSprite_;

#pragma endregion

#pragma region OBJ
	std::unique_ptr<Object3d> tyoinoriObj;
	std::unique_ptr<Model> tyoinori;

	std::unique_ptr<Object3d> skydomeObj;
	std::unique_ptr<Model> skydome;
#pragma endregion


	//ImGuiデバッグ用
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	Mathematics::Vector2 pos = { 0,0 };

	float rot = 0.0f;
};


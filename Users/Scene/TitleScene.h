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

// �^�C�g���V�[��
class TitleScene : public BaseScene
{
public: // �����o�֐�

	TitleScene() = default;
	~TitleScene() = default;

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


	//ImGui�f�o�b�O�p
	Mathematics::Vector3 cameraPos = { 0,0,0 };

	Mathematics::Vector2 pos = { 0,0 };

	float rot = 0.0f;
};


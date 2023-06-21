#pragma once
#include "BaseScene.h"
#include "AbstractSceneFactory.h"

class SceneManager final
{
public: // �����o�֐�

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	// ���̃V�[���\��
	void SetSceneFactory(AbstractSceneFactory* sceneFactory);
	void ChangeScene(const std::string& sceneName);

	static SceneManager* GetInstance();

private:
	// ���̃V�[���i���s���V�[���j
	BaseScene* scene_ = nullptr;
	BaseScene* nextScene_ = nullptr;

	// �V�[���t�@�N�g���[
	AbstractSceneFactory* sceneFactory_ = nullptr;

	SceneManager() = default;
	~SceneManager() = default;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};


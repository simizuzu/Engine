#pragma once
#include "BaseScene.h"

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
	void SetNextScene(BaseScene* nextScene);

	static SceneManager* GetInstance();

private:
	// ���̃V�[���i���s���V�[���j
	BaseScene* scene_ = nullptr;
	BaseScene* nextScene_ = nullptr;

	SceneManager() = default;
	~SceneManager() = default;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;
};


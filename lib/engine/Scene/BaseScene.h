#pragma once

// �O���錾
class SceneManager;

// �V�[�����N���X
class BaseScene
{
public: // �����o�֐�

	virtual ~BaseScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize() = 0;

public:
	virtual void SetSceneManager(SceneManager* sceneManager);

private:
	// �V�[���}�l�[�W���i�؂�Ă���j
	SceneManager* sceneManager_ = nullptr;
};


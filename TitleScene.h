#pragma once
#include "BaseScene.h"

// �^�C�g���V�[��
class TitleScene : BaseScene
{
public: // �����o�֐�

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

};


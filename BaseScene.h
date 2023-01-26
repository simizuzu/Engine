#pragma once

// �V�[�����N���X
class BaseScene
{
public: // �����o�֐�

	virtual ~BaseScene() = default;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();
	
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	virtual void Finalize();
};


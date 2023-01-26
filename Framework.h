#pragma once

// �Q�[���S��
class Framework
{
public: // �����o�֐�
	virtual ~Framework() = default;
	// ������
	virtual void Initialize();
	// �X�V
	virtual void Finalize();
	// ���t���[���X�V
	virtual void Update();
	// �`��
	virtual void Draw() = 0;
	// �I���`�F�b�N
	virtual bool IsEndRequest();

	// ���s
	void Run();

private:
	// �Q�[���I���t���O
	bool endRequest_ = false;

	
};


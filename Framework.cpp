#include "Framework.h"

void Framework::Initialize()
{

}

void Framework::Finalize()
{
	
}

void Framework::Update()
{
	
}

void Framework::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v
	{
		// ���t���[���X�V
		Update();
		// �I�����N�G�X�g�������甲����
		if (IsEndRequest())
		{
			break;
		}
		// �`��
		Draw();
	}
	// �Q�[���I��
	Finalize();
}

bool Framework::IsEndRequest()
{
	return endRequest_;
}

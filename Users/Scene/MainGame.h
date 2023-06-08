#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include "Light.h"
#include "Framework.h"
#include "SceneFactory.h"

// �Q�[���S��
class MainGame : public Framework
{
public: // �����o�֐�
	MainGame() = default;
	~MainGame() = default;

	// ������
	void Initialize() override;
	// �I��
	void Finalize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �Q�[���I���t���O
	bool endRequest_ = false;
};


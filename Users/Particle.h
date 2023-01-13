#pragma once
#include "Sprite2D.h"
#include "Input.h"
#include "TextureManager.h"
#include "Transform.h"

struct Hexagon
{
	Transform transform;
	float timer = 120;
	char PADING[4]{};
};

class SceneParticle
{
public:

	SceneParticle() = default;
	~SceneParticle() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	///<summary>
	///�p�[�e�B�N���X�^�[�g
	///<summary>
	void state();

	/// <summary>
	/// �A�C�L���b�`
	/// </summary>
	void EyeCatch();

	/// <summary>
	/// �A�C�L���b�`�̏�����
	/// </summary>
	void EyeCatchInitialize();

	/// <summary>
	/// �A�C�L���b�`�̕`��
	/// </summary>
	void EyeCatchDraw();

	/// <summary>
	/// �l�̏�����
	/// </summary>
	void Reset();

	float GetNumTimer();

	EngineMathF::Vector2 pos;
	EngineMathF::Vector2 pos2;
	EngineMathF::Vector2 bottom;

	bool flag = false;
	bool flag2 = false;
	bool flag3 = false;
	char PADING[5]{};

private:
	// �e�N�X�`���n���h��
	TextureData textureHandle_;
	TextureData textureBox_;
	// �X�v���C�g
	std::list<Hexagon> hexagon_;
	std::list<Hexagon> hexagon2_;
	Transform spriteBoxTransform;
	std::unique_ptr<Sprite2D> sprite_;
	std::unique_ptr<Sprite2D> spriteBox_;
	Input* input_ = nullptr;

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	SceneParticle& operator=(const SceneParticle&) = delete;
	SceneParticle(const SceneParticle&) = delete;
};


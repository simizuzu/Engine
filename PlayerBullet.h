#pragma once
#include "Model.h"
#include "Object3d.h"
#include "Input.h"

class PlayerBullet
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:
	
	std::unique_ptr<Model> bulletModel_;
	std::unique_ptr<Object3d> bulletObject_;
};


#pragma once
#include <memory>

#include "Camera.h"
#include "Object3d.h"
#include "Input.h"

class GameCamera
{
private:
	//�X�s�[�h
	float speed_ = 2.0f;
	const float minSpeed_ = 2.0f;
	const float maxSpeed_ = 50.0f;
	Mathematics::Vector3 moveSpeed_ = { 0.0f,0.0f,speed_ };
	Mathematics::Vector3 rotSpeed_ = { 0.0f,0.0f,0.0f };
	//�����x
	float acceleration_ = 0.0f;
	float accelerationSpeed_ = 1.0f;
	char PADING[4]{};
	Input* input_ = nullptr;

	std::unique_ptr<Camera> GameCamera_;

	Mathematics::Vector3 front_ = { 0.0f,0.0f,speed_ };
	Object3d GameCameraTransform_;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	Camera* GetCamera();
	float GetSpeed();
	Object3d* GetTransform();
	Mathematics::Vector3 GetWorldPosition();
	void SetPos(Mathematics::Vector3 pos);

	Mathematics::Vector3 GetFront();

	GameCamera() = default;
	~GameCamera() = default;

private:
	void Move();
	void ThirdPersonUpdate(Mathematics::Vector3& move, Mathematics::Vector3& rot);

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameCamera& operator=(const GameCamera&) = delete;
	GameCamera(const GameCamera&) = delete;
};


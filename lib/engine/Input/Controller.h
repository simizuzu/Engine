#pragma once
#include "Vector2.h"
#include <Windows.h>
#include <Xinput.h>

#pragma comment (lib, "xinput.lib")

enum ControllerButton
{
	B = XINPUT_GAMEPAD_B,
	A = XINPUT_GAMEPAD_A,
	X = XINPUT_GAMEPAD_X,
	Y = XINPUT_GAMEPAD_Y,
	START = XINPUT_GAMEPAD_START,
	BACK = XINPUT_GAMEPAD_BACK,
	LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LT,
	RT
};

enum ControllerStick
{
	L_UP, L_DOWN, L_LEFT, L_RIGHT,
	R_UP, R_DOWN, R_LEFT, R_RIGHT, XBOX_STICK_NUM
};

class Controller
{
private:
	XINPUT_STATE xinputState{};
	XINPUT_STATE oldXinputState{};

	// �R���g���[���[�U������
	float shakePower = 0.0f;
	// �R���g���[���[�U������(�t���[����)
	int shakeTimer = 0;

	// �f�b�h�]�[���ɓ����Ă��邩(DeadRate : �f�b�h�]�[������̓x����)
	bool StickDeadZone(MyMath::Vector2& stick, const MyMath::Vector2& deadZoneInitial);

	// �ō����͒l
	const float MAX_STICK_NUM = 32768.0f;

public:
	Controller() = default;
	~Controller() = default;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �g���K�[�{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N����{�^��</param>
	/// <returns></returns>
	bool TriggerButton(ControllerButton button);

	/// <summary>
	/// �g���K�[�X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stickInput">�X�e�B�b�N�̕���</param>
	/// <param name="deadZoneRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadZoneInitial">�f�b�h�]�[���̔���̏����l: 1.0f</param>
	/// <returns></returns>
	bool TriggerStick(ControllerStick stickInput, const float& deadZoneRange = 0.3f, const MyMath::Vector2& deadZoneInitial = { 1.0f,1.0f });

	/// <summary>
	/// �v�b�V���{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N����{�^��</param>
	/// <returns></returns>
	bool PushButton(ControllerButton button);

	/// <summary>
	/// �X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stickInput">�X�e�B�b�N�̕���</param>
	/// <param name="deadZoneRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadZoneInitial">�f�b�h�]�[���̔���̏����l: 1.0f</param>
	/// <returns></returns>
	bool InputStick(ControllerStick stickInput, const float& deadZoneRange = 0.3f, const MyMath::Vector2& deadZoneInitial = { 1.0f,1.0f });

	/// <summary>
	/// �{�^���𗣂����Ƃ��̓���
	/// </summary>
	/// <param name="button">�`�F�b�N����{�^��</param>
	/// <returns></returns>
	bool ReleaseTriggerButton(ControllerButton button);

	/// <summary>
	/// �X�e�B�b�N�̗������Ƃ��̓���
	/// </summary>
	/// <param name="stickInput">�X�e�B�b�N�̕���</param>
	/// <param name="deadZoneRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadZoneInitial">�f�b�h�]�[���̔���̏����l: 1.0f</param>
	/// <returns></returns>
	bool ReleaseTriggerStick(ControllerStick stickInput, const float& deadZoneRange = 0.3f, const MyMath::Vector2& deadZoneInitial = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̐U�������鏈��
	/// </summary>
	/// <param name="power">�U���̋���: 0.0f~1.0f</param>
	/// <param name="flame">�U�������鎞��(�t���[����)</param>
	void ShakeController(const float& power, const int& flame);

	/// <summary>
	/// ���X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadZoneRange">�f�b�h�]�[���̔���̏����l: 1.0f</param>
	/// <returns></returns>
	MyMath::Vector2 GetLeftStickVec(const MyMath::Vector2& deadZoneRange = { 1.0f,1.0f });

	/// <summary>
	/// �E�X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadZoneRange">�f�b�h�]�[���̔���̏����l: 1.0f</param>
	/// <returns></returns>
	MyMath::Vector2 GetRightStickVec(const MyMath::Vector2& deadZoneRange = { 1.0f,1.0f });

private:
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	Controller& operator=(const Controller&) = delete;
	Controller(const Controller&) = delete;
};


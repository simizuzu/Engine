#pragma once
#include "Camera.h"
#include "Object3d.h"

class RailCamera
{
public:
	RailCamera();
	~RailCamera();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const Mathematics::Vector3& position, const Mathematics::Vector3& rotaion);

	/// <summary>
	/// ���t���[������
	/// </summary>
	bool Update(bool GetCrashFlag, int frequencyInvocationDoor);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �^�C�g������Q�[���Ɉڍs����Ƃ��Ƀ��Z�b�g����
	/// </summary>
	void reset();

	/// <summary>
	/// ������邲�ƂɃ��Z�b�g���郂�m���܂Ƃ߂�
	/// </summary>
	void lapReset();

	void SpeedUp();

	void SpeedDown();

	Camera* GetViewProjection();

	Object3d* GetWorldTransformPtr();

	float GetWorldTransformRot();

	int GetLap();

	void addRot(Mathematics::Vector3 rot);
	void addTranslation(Mathematics::Vector3 translation);

	void setTranslation(Mathematics::Vector3 translation);

	void setSpeed(float speed_);

	bool GetIsRapReset();

	Mathematics::Vector3 GetVector();
private:

	std::unique_ptr<Camera> viewProjection_;
	std::unique_ptr<Object3d> worldTransform_;

	Mathematics::Vector3 vector = { 0,0,0 };

	float rotRange[6] = {};

	float speed = 1.0f;

	enum class side {
		First = 1,//���
		Second,//���
		Third,//�O��
		Fourth,//�l��
		Fifth,//�ܔ�
		Sixth//�Z��
	};

	side currentSide = side::First;

	int lap = 0;

	bool IsLapReset = false;
	void Move();

	float invocationTrnsDoor[4] = {};
	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	RailCamera& operator=(const RailCamera&) = delete;
	RailCamera(const RailCamera&) = delete;
};


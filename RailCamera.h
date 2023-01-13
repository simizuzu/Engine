#pragma once
#include "Camera.h"
#include "Object3d.h"

class RailCamera
{
public:
	RailCamera();
	~RailCamera();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Mathematics::Vector3& position, const Mathematics::Vector3& rotaion);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	bool Update(bool GetCrashFlag, int frequencyInvocationDoor);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// タイトルからゲームに移行するときにリセットする
	/// </summary>
	void reset();

	/// <summary>
	/// 一周するごとにリセットするモノをまとめる
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
		First = 1,//一番
		Second,//二番
		Third,//三番
		Fourth,//四番
		Fifth,//五番
		Sixth//六番
	};

	side currentSide = side::First;

	int lap = 0;

	bool IsLapReset = false;
	void Move();

	float invocationTrnsDoor[4] = {};
	//コピーコンストラクタ・代入演算子削除
	RailCamera& operator=(const RailCamera&) = delete;
	RailCamera(const RailCamera&) = delete;
};


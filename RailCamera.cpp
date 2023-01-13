#include "RailCamera.h"

RailCamera::RailCamera()
{
}

RailCamera::~RailCamera()
{
}

void RailCamera::Initialize(const Mathematics::Vector3& position, const Mathematics::Vector3& rotaion)
{
	//ワールドトランスフォームの初期設定
	worldTransform_->position = position;
	worldTransform_->rotation = rotaion;

	viewProjection_ = std::make_unique<Camera>();
	viewProjection_->SetFarZ(12000.0f);
	//ビュープロジェクションの初期化
	viewProjection_->Initialize();

	Mathematics::Vector3 start = { 0.0f,0.0f,0.0f };
	Mathematics::Vector3 gole = { 7.5f,0.0f,static_cast<float> (7.5 * sqrt(3)) };
	vector = { gole.x - start.x,gole.y - start.y,gole.z - start.z };
	vector = vector.normalize();

	rotRange[0] = 750.0f;
	rotRange[1] = rotRange[0] + vector.z * 750;
	rotRange[2] = 750.0f;
	rotRange[3] = 0.0f;
	rotRange[4] = rotRange[3] - vector.z * 750;
	rotRange[5] = 0.0f;

	invocationTrnsDoor[0] = 750 + 365 * vector.z;
	invocationTrnsDoor[1] = 610 * -vector.z;
	invocationTrnsDoor[2] = 460 * -vector.z;
	invocationTrnsDoor[3] = 310 * -vector.z;
}

bool RailCamera::Update(bool GetCrashFlag, int frequencyInvocationDoor)
{
	float playerz = 0.0f;

	if (!GetCrashFlag)
	{
		switch (currentSide)
		{
		case side::First:

			playerz = worldTransform_->position.z + 10.0f;
			if (playerz < rotRange[0] - (speed * 10))
			{
				Mathematics::Vector3 move = { 0,0,1.0f * speed };
				worldTransform_->position += move;
				if (playerz > rotRange[0] - (speed * 10))
				{
					worldTransform_->position = Mathematics::Vector3{ 0.0f,0.0f,rotRange[0] - speed * 10 };
				}
			}
			else
			{
				Mathematics::Vector3 move = { 0,0,1.0f * speed };
				Mathematics::Vector3 Rot = { 0,3.0f * MyMathUtility::degree2Radius,0 };

				if (worldTransform_->rotation.y >= 30.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { -vector.x * 10,0.0f,rotRange[0] - vector.z * 10 };

					currentSide = side::Second;
				}
				else
				{
					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;
				}
				if (worldTransform_->rotation.y > 30.0f * EngineMathF::Deg2Rad)
				{
					worldTransform_->rotation.y = 30.0f * EngineMathF::Deg2Rad;
				}
			}
			break;
		case side::Second:
			playerz = worldTransform_->position.z + vector.z * 10;
			if (playerz < rotRange[1] - (vector.z * speed * 10))
			{
				EngineMathF::Vector3 move = { vector * speed };
				worldTransform_->position += move;
				if (playerz > rotRange[1] - (vector.z * speed * 10))
				{
					worldTransform_->position = EngineMathF::Vector3{ 0.0f,0.0f,rotRange[2] - (vector.z * speed * 10) };
				}
			}
			else
			{
				EngineMathF::Vector3 move = { vector * speed };
				EngineMathF::Vector3 Rot = { 0,12 * MyMathUtility::degree2Radius,0 };

				if (worldTransform->rotation.y >= 150.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { vector.x * 750 - vector.x * 10,0.0f,rotRange[1] + vector.z * 10 };
					currentSide = side::Third;
				}
				else
				{
					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;
				}
				if (worldTransform_->rotation.y > 150.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->rotation.y = 150.0f * MyMathUtility::degree2Radius;
				}
			}
			break;
		case side::Third:
			playerz = worldTransform_->position.z - vector.z * 10.0f;
			if (playerz > rotRange[2] + vector.z * (speed * 10))
			{
				EngineMathF::Vector3 move = { vector.x * speed,vector.y * speed,-vector.z * speed };
				worldTransform_->position += move;
				if (playerz < rotRange[2] + (vector.z * speed * 10))
				{
					worldTransform_->position = EngineMathF::Vector3{ 0.0f,0.0f,rotRange[2] + (vector.z * speed * 10) };
				}
			}
			else
			{
				EngineMathF::Vector3 move = { vector.x * speed,vector.y * speed,-vector.z * speed };
				EngineMathF::Vector3 Rot = { 0,3 * MyMathUtility::degree2Radius,0 };

				if (worldTransform_->rotation.y >= 180.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { vector.x * 750 * 2,0.0f,750 + 10 };
					currentSide = side::Fourth;
				}
				else
				{
					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;
				}
				if (worldTransform_->rotation.y > 180.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->rotation.y = 180.0f * MyMathUtility::degree2Radius;
				}
			}
			break;
		case side::Fourth:
			playerz = worldTransform_->position.z - 10.0f;
			if (playerz > rotRange[3] + speed * 10)
			{
				EngineMathF::Vector3 move = { 0,0,-1.0f * speed };
				worldTransform_->position += move;
				if (playerz < rotRange[3] + speed * 10)
				{
					worldTransform_->position = EngineMathF::Vector3{ 0.0f,0.0f,rotRange[3] + (speed * 10) };
				}
			}
			else
			{
				EngineMathF::Vector3 move = { 0,0,-1.0f * speed };
				EngineMathF::Vector3 Rot = { 0,3 * EngineMathF::Deg2Rad,0 };

				if (worldTransform_->rotation.y >= 210.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { vector.x * 750 * 2 + vector.x * 10,0.0f,vector.z * 10 };
					currentSide = side::Fifth;
				}
				else
				{
					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;
				}
				if (worldTransform_->rotation.y > 210.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->rotation.y = 210.0f * MyMathUtility::degree2Radius;
				}
			}
			break;
		case side::Fifth:
			playerz = worldTransform_->position.z - vector.z * 10.0f;
			if (playerz > rotRange[4] + speed * 10)
			{
				EngineMathF::Vector3 move = { -vector.x * speed,-vector.y * speed,-vector.z * speed };
				worldTransform_->position += move;
				if (playerz < rotRange[4] + speed * 10)
				{
					worldTransform_->position = EngineMathF::Vector3{ 0.0f,0.0f,rotRange[4] + (speed * 10) };
				}
			}
			else
			{
				EngineMathF::Vector3 move = { -vector.x * speed,-vector.y * speed,-vector.z * speed };
				EngineMathF::Vector3 Rot = { 0,12 * EngineMathF::Deg2Rad,0 };

				if (worldTransform_->rotation.y >= 330.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { vector.x * 750 + vector.x * 10,0,rotRange[4] - vector.z * 10 };

					currentSide = side::Sixth;
				}
				else
				{
					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;
				}
				if (worldTransform_->rotation.y > 330.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->rotation.y = 330.0f * MyMathUtility::degree2Radius;
				}
			}
			break;
		case side::Sixth:
			playerz = worldTransform_->position.z + vector.z * 10.0f;
			if (playerz < rotRange[5] - speed * 10)
			{
				EngineMathF::Vector3 move = { -vector.x * speed,vector.y * speed,vector.z * speed };
				worldTransform_->position += move;
				if (playerz > rotRange[5] - speed * 10)
				{
					worldTransform_->position = EngineMathF::Vector3{ 0.0f,0.0f,rotRange[5] - (speed * 10) };
				}
			}
			else
			{
				EngineMathF::Vector3 move = { -vector.x * speed,vector.y * speed,vector.z * speed };

				if (worldTransform_->rotation.y >= 360.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->position = { 0.0,0.0f,-10.0f };

					worldTransform_->rotation.y = 0.0f;

					lap++;

					currentSide = side::First;
				}
				else
				{
					EngineMathF::Vector3 Rot = { 0,3 * EngineMathF::Deg2Rad,0 };

					worldTransform_->rotation += (Rot);
					worldTransform_->position += move;

					IsLapReset = true;
				}
				if (worldTransform_->rotation.y > 360.0f * MyMathUtility::degree2Radius)
				{
					worldTransform_->rotation.y = 360.0f * MyMathUtility::degree2Radius;
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		speed = 0.8f;

		switch (currentSide)
		{
		case side::First:
			playerz = worldTransform_->position.z - 10.0f;
			if (playerz < rotRange[0])
			{
				EngineMathF::Vector3 move = { 0,0,1.0f * speed };
				worldTransform_->position += move;
			}
			else if (playerz >= rotRange[0])
			{
				EngineMathF::Vector3 Rot = { 0,30 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { -vector.x * 10,0.0f,-vector.z * 10 + 750 };

				currentSide = side::Second;
			}
			break;
		case side::Second:
			playerz = worldTransform_->position.z - vector.z * 10;
			if (playerz < rotRange[1])
			{
				EngineMathF::Vector3 move = { vector * speed };
				worldTransform_->position += move;
			}
			else if (playerz >= rotRange[1])
			{
				EngineMathF::Vector3 Rot = { 0,120 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { vector.x * 750 - vector.x * 10,0.0f,rotRange[1] + vector.z * 10 };
				currentSide = side::Third;
			}
			break;
		case side::Third:
			playerz = worldTransform_->position.z + vector.z * 10.0f;
			if (playerz > rotRange[2])
			{
				EngineMathF::Vector3 move = { vector.x * speed,vector.y * speed ,-vector.z * speed };
				worldTransform_->position += move;
			}
			else if (playerz <= rotRange[2])
			{
				EngineMathF::Vector3 Rot = { 0,30 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { vector.x * 750 * 2,0.0f,750 + 10 };

				currentSide = side::Fourth;
			}
			break;
		case side::Fourth:
			playerz = worldTransform_->position.z + 10.0f;
			if (playerz > rotRange[3])
			{
				EngineMathF::Vector3 move = { 0,0,-1.0f * speed };
				worldTransform_->position += move;
			}
			if (playerz <= rotRange[3])
			{
				EngineMathF::Vector3 Rot = { 0,30 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { vector.x * 750 * 2 + vector.x * 10,0.0f,vector.z * 10 };

				currentSide = side::Fifth;
			}
			break;
		case side::Fifth:
			playerz = worldTransform_->position.z + vector.z * 10.0f;
			if (playerz > rotRange[4])
			{
				EngineMathF::Vector3 move = { -vector.x * speed,-vector.y * speed,-vector.z * speed };
				worldTransform_->position += move;
			}
			else if (playerz <= rotRange[4])
			{
				EngineMathF::Vector3 Rot = { 0,120 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { vector.x * 750 + vector.x * 10,0,rotRange[4] - vector.z * 10 };

				currentSide = side::Sixth;
			}
			break;
		case side::Sixth:
			playerz = worldTransform_->position.z - vector.z * 10.0f;
			if (playerz < rotRange[5])
			{
				EngineMathF::Vector3 move = { -vector.x * speed ,vector.y * speed ,vector.z * speed };
				worldTransform_->position += move;
			}
			else if (playerz >= rotRange[5])
			{
				EngineMathF::Vector3 Rot = { 0,30 * EngineMathF::Deg2Rad,0 };

				worldTransform_->rotation += (Rot);
				worldTransform_->position = { 0.0,0.0f,-10.0f };

				IsLapReset = true;

				lap++;

				currentSide = side::First;
			}
			break;
		default:
			break;
		}
	}

	Move();


	if (currentSide == side::Second && playerz >= invocationTrnsDoor[0] && frequencyInvocationDoor == 0)
	{
		return true;
	}
	if (currentSide == side::Sixth && playerz >= invocationTrnsDoor[1] && frequencyInvocationDoor == 1)
	{
		return true;
	}
	if (currentSide == side::Sixth && playerz >= invocationTrnsDoor[2] && frequencyInvocationDoor == 2)
	{
		return true;
	}
	if (currentSide == side::Sixth && playerz >= invocationTrnsDoor[3] && frequencyInvocationDoor == 3)
	{
		return true;
	}

	return false;
}

void RailCamera::Draw()
{
}

void RailCamera::reset()
{
}

void RailCamera::lapReset()
{
}

void RailCamera::SpeedUp()
{
}

void RailCamera::SpeedDown()
{
}

Camera* RailCamera::GetViewProjection()
{
	return nullptr;
}

Object3d* RailCamera::GetWorldTransformPtr()
{
	return nullptr;
}

float RailCamera::GetWorldTransformRot()
{
	return 0.0f;
}

int RailCamera::GetLap()
{
	return 0;
}

void RailCamera::addRot(Mathematics::Vector3 rot)
{
}

void RailCamera::addTranslation(Mathematics::Vector3 translation)
{
}

void RailCamera::setTranslation(Mathematics::Vector3 translation)
{
}

void RailCamera::setSpeed(float speed_)
{
}

bool RailCamera::GetIsRapReset()
{
	return false;
}

Mathematics::Vector3 RailCamera::GetVector()
{
	return Mathematics::Vector3();
}

void RailCamera::Move()
{
}

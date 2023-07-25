#include "SplinePosCamera.h"

SplinePosCamera::SplinePosCamera(MyMath::Vector3& Start, MyMath::Vector3& p1, MyMath::Vector3& p2, MyMath::Vector3& end)
{
	std::vector<MyMath::Vector3> points{ Start, Start, p1, p2, end, end };
	this->points = points;
}

SplinePosCamera::SplinePosCamera(const std::vector<MyMath::Vector3>& points)
{
	this->points = points;
}

SplinePosCamera::~SplinePosCamera() {}

void SplinePosCamera::Update(float& time)
{
	timeRate_ += time;
	if (timeRate_ >= MaxTime)
	{
		if (startIndex < points.size() - 3)
		{
			startIndex += 1;
			timeRate_ -= MaxTime;
		}
		else
		{
			timeRate_ = MaxTime;
		}
	}
	NowPos = SplinePositionUpdate(points, startIndex, timeRate_);
}

MyMath::Vector3 SplinePosCamera::SplinePositionUpdate(const std::vector<MyMath::Vector3>& points, size_t& startIndex, float& t)
{
	//��Ԃ��ׂ��_�̐�
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];
	if (startIndex < 1)return points[1];

	MyMath::Vector3 p0 = points[startIndex - 1];
	MyMath::Vector3 p1 = points[startIndex];
	MyMath::Vector3 p2 = points[startIndex + 1];
	MyMath::Vector3 p3 = points[startIndex + 2];

	MyMath::Vector3 position = 0.5 * (2 * p1 + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) + (-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t));

	return position;
}
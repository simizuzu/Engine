#include "Collision.h"

bool Collision::CheckSpere2Plane(const Sphere& sphere, const Plane& plane, MyMath::Vector4* inter)
{
	float distV = sphere.center.dot(plane.normal);

	float dist = distV - plane.distance;

	if (fabs(dist) > sphere.radius)
	{
		return false;
	}

// �[����_���v�Z
	if (inter)
	{
		// ���ʏ�̍Đڋߓ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

bool Collision::CheckOBBToOBB(BoundingBox& obb1, BoundingBox& obb2)
{
    //�e�����x�N�g���̊m��
    //(N***:�W���������x�N�g��)
    MyMath::Vector3 NAe1 = obb1.GetDirectVec(0), Ae1 = NAe1 * obb1.GetLength(0);
    MyMath::Vector3 NAe2 = obb1.GetDirectVec(1), Ae2 = NAe2 * obb1.GetLength(1);
    MyMath::Vector3 NAe3 = obb1.GetDirectVec(2), Ae3 = NAe3 * obb1.GetLength(2);
    MyMath::Vector3 NBe1 = obb1.GetDirectVec(0), Be1 = NBe1 * obb1.GetLength(0);
    MyMath::Vector3 NBe2 = obb1.GetDirectVec(1), Be2 = NBe2 * obb1.GetLength(1);
    MyMath::Vector3 NBe3 = obb1.GetDirectVec(2), Be3 = NBe3 * obb1.GetLength(2);
    MyMath::Vector3 interval = obb1.GetCenter() - obb2.GetCenter();

    //������:Ae1
    float rA = Ae1.length();
    float rB = MyMath::LenSegLineOfSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    float L = fabs(interval.dot(NAe1));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Ae2
    rA = Ae2.length();
    rB = MyMath::LenSegLineOfSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = fabs(interval.dot(NAe2));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Ae3
    rA = Ae3.length();
    rB = MyMath::LenSegLineOfSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = fabs(interval.dot(NAe3));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be1
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = Be1.length();
    L = fabs(interval.dot(NBe1));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be2
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = Be2.length();
    L = fabs(interval.dot(NBe2));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be3
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = Be3.length();
    L = fabs(interval.dot(NBe3));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C11
    MyMath::Vector3 Cross;
    Cross = NAe1.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C12
    Cross = NAe1.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C12
    Cross = NAe1.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C21
    Cross = NAe2.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C22
    Cross = NAe2.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C23
    Cross = NAe2.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C31
    Cross = NAe3.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C32
    Cross = NAe3.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C33
    Cross = NAe3.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    // �Փ˂��Ă���
    return true;
}

bool Collision::CheckOBBToOBB(BoundingBox* obb1, BoundingBox* obb2)
{
    if (!obb1 || !obb2)
    {
        return false;
    }

    //�e�����x�N�g���̊m��
    //(N***:�W���������x�N�g��)
    MyMath::Vector3 NAe1 = obb1->GetDirectVec(0), Ae1 = NAe1 * obb1->GetLength(0);
    MyMath::Vector3 NAe2 = obb1->GetDirectVec(1), Ae2 = NAe2 * obb1->GetLength(1);
    MyMath::Vector3 NAe3 = obb1->GetDirectVec(2), Ae3 = NAe3 * obb1->GetLength(2);
    MyMath::Vector3 NBe1 = obb2->GetDirectVec(0), Be1 = NBe1 * obb2->GetLength(0);
    MyMath::Vector3 NBe2 = obb2->GetDirectVec(1), Be2 = NBe2 * obb2->GetLength(1);
    MyMath::Vector3 NBe3 = obb2->GetDirectVec(2), Be3 = NBe3 * obb2->GetLength(2);
    MyMath::Vector3 Interval = obb1->GetCenter() - obb2->GetCenter();

    //������:Ae1
    float rA = Ae1.length();
    float rB = MyMath::LenSegLineOfSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    float L = fabs(Interval.dot(NAe1));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Ae2
    rA = Ae2.length();
    rB = MyMath::LenSegLineOfSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = fabs(Interval.dot(NAe2));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Ae3
    rA = Ae3.length();
    rB = MyMath::LenSegLineOfSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = fabs(Interval.dot(NAe3));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be1
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = Be1.length();
    L = fabs(Interval.dot(NBe1));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be2
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = Be2.length();
    L = fabs(Interval.dot(NBe2));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:Be3
    rA = MyMath::LenSegLineOfSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = Be3.length();
    L = fabs(Interval.dot(NBe3));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C11
    MyMath::Vector3 Cross;
    Cross = NAe1.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C12
    Cross = NAe1.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C13
    Cross = NAe1.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C21
    Cross = NAe2.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C22
    Cross = NAe2.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C23
    Cross = NAe2.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C31
    Cross = NAe3.cross(NBe1);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C32
    Cross = NAe3.cross(NBe2);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    //������:C33
    Cross = NAe3.cross(NBe3);
    rA = MyMath::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = MyMath::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Interval.dot(Cross));
    if (L > rA + rB)
    {
        //�Փ˂��Ă��Ȃ�
        return false;
    }

    // �Փ˂��Ă���
    return true;
}

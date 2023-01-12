#include "Collision.h"

bool Collision::CheckOBBToOBB(BoundingBox& obb1, BoundingBox& obb2)
{
    //各方向ベクトルの確保
    //(N***:標準化方向ベクトル)
    Mathematics::Vector3 NAe1 = obb1.GetDirectVec(0), Ae1 = NAe1 * obb1.GetLength(0);
    Mathematics::Vector3 NAe2 = obb1.GetDirectVec(1), Ae2 = NAe2 * obb1.GetLength(1);
    Mathematics::Vector3 NAe3 = obb1.GetDirectVec(2), Ae3 = NAe3 * obb1.GetLength(2);
    Mathematics::Vector3 NBe1 = obb1.GetDirectVec(0), Be1 = NBe1 * obb1.GetLength(0);
    Mathematics::Vector3 NBe2 = obb1.GetDirectVec(1), Be2 = NBe2 * obb1.GetLength(1);
    Mathematics::Vector3 NBe3 = obb1.GetDirectVec(2), Be3 = NBe3 * obb1.GetLength(2);
    Mathematics::Vector3 interval = obb1.GetCenter() - obb2.GetCenter();

    //分離軸:Ae1
    float rA = Ae1.length();
    float rB = Mathematics::LenSegLineOfSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    float L = fabs(interval.dot(NAe1));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:Ae2
    rA = Ae2.length();
    rB = Mathematics::LenSegLineOfSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = fabs(interval.dot(NAe2));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:Ae3
    rA = Ae3.length();
    rB = Mathematics::LenSegLineOfSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = fabs(interval.dot(NAe3));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:Be1
    rA = Mathematics::LenSegLineOfSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = Be1.length();
    L = fabs(interval.dot(NBe1));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:Be2
    rA = Mathematics::LenSegLineOfSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = Be2.length();
    L = fabs(interval.dot(NBe2));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:Be3
    rA = Mathematics::LenSegLineOfSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = Be3.length();
    L = fabs(interval.dot(NBe3));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C11
    Mathematics::Vector3 Cross;
    Cross = NAe1.cross(NBe1);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C12
    Cross = NAe1.cross(NBe2);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C12
    Cross = NAe1.cross(NBe3);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C21
    Cross = NAe2.cross(NBe1);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C22
    Cross = NAe2.cross(NBe2);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C23
    Cross = NAe2.cross(NBe3);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C31
    Cross = NAe3.cross(NBe1);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C32
    Cross = NAe3.cross(NBe2);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    //分離軸:C33
    Cross = NAe3.cross(NBe3);
    rA = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = Mathematics::LenSegLineOfSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(interval.dot(Cross));
    if (L > rA + rB)
    {
        //衝突していない
        return false;
    }

    // 衝突している
    return true;
}

bool Collision::CheckOBBToOBB(BoundingBox* obb1, BoundingBox* obb2)
{
    if (!obb1 || !obb2)
    {
        return false;
    }
    return true;
}

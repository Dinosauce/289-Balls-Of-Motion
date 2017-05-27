#include "AABB.h"

void setAABB(AABB* newAABB, float xMin, float yMin, float zMin, float xMax, float yMax, float zMax)
{
    newAABB->pMin[0] = xMin;
    newAABB->pMin[1] = yMin;
    newAABB->pMin[2] = zMin;

    newAABB->pMax[0] = xMax;
    newAABB->pMax[1] = yMax;
    newAABB->pMax[2] = zMax;

    newAABB->normal[0] = 0;
    newAABB->normal[1] = 0;
    newAABB->normal[2] = 0;

    normalize(newAABB->normal);
}

void setNormal(AABB* aabb, float x, float y, float z)
{
    aabb->normal[0] = x;
    aabb->normal[1] = y;
    aabb->normal[2] = z;

    normalize(aabb->normal);
}

void clamp(AABB* aabb, vect3 point, vect3 out)
{
	out[0] = clampF(aabb->pMin[0], aabb->pMax[0], point[0]);
	out[1] = clampF(aabb->pMin[1], aabb->pMax[1], point[1]);
	out[2] = clampF(aabb->pMin[2], aabb->pMax[2], point[2]);
}

// TODO: Implement fully: currently incomplete
//void clampWall(AABB* aabb, vect3 point, float buffer)
//{
//    int i;
//    vect3 p;
//    clamp(aabb, point, p);
//
//    // If the point is outside aabb, use clamp values
//    if (equals(p, point));
//    {
//        for (i = 0; i < 3; i++)
//            point[i] += aabb->normal[i] * buffer;
//    }
//    // the point is inside the aabb, set point to closest point on surface
//    else
//    {
//
//    }
//}

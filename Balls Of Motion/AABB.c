#include "AABB.h"

void setAABB(AABB* newAABB, float xMin, float yMin, float zMin, float xMax, float yMax, float zMax)
{
    newAABB->pMin[0] = xMin;
    newAABB->pMin[1] = yMin;
    newAABB->pMin[2] = zMin;

    newAABB->pMax[0] = xMax;
    newAABB->pMax[1] = yMax;
    newAABB->pMax[2] = zMax;
}

void setNormal(AABB* aabb, float x, float y, float z)
{
    aabb->normal[0] = x;
    aabb->normal[1] = y;
    aabb->normal[2] = z;
}

void clamp(AABB* aabb, vect3 point, vect3 out)
{
	out[0] = clampF(aabb->pMin[0], aabb->pMax[0], point[0]);
	out[1] = clampF(aabb->pMin[1], aabb->pMax[1], point[1]);
	out[2] = clampF(aabb->pMin[2], aabb->pMax[2], point[2]);
}

#ifndef AABB_H
#define AABB_H

#include <GL/glut.h>
#include "Extra.h"

typedef struct{
    vect3 pMin;
    vect3 pMax;
    vect3 normal;
} AABB;

    /** Initializes a static AABB
     *
     * \param newAABB - AABB to initialize
     * \param xMin - minPoint
     * \param yMin - minPoint
     * \param zMin - minPoint
     * \param xMax - maxPoint
     * \param yMax - maxPoint
     * \param zMax - maxPoint
     */
    void setAABB(AABB* newAABB, float xMin, float yMin, float zMin, float xMax, float yMax, float zMax);
    void setNormal(AABB* aabb, float x, float y, float z);

	void Clamp(AABB* aabb, vect3 point, vect3 out);

#endif // AABB_H

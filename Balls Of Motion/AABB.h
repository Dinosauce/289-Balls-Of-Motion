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

    /// Sets the normal to given values and normalize
    void setNormal(AABB* aabb, float x, float y, float z);

    /// Clamps the point to within the aabb and sets it to out
	void clamp(AABB* aabb, vect3 point, vect3 out);

	//TODO: Implement for collision detection; as collisions required the
    // intersection point (or closest point to the surface) with the aabb
    // not a position within the aabb (which clamp may return)
    // /// Moves the point to a point on the aabbs exterior (in direction of normal) and extends by buffer.
	// void clampWall(AABB* aabb, vect3 point, float buffer);

#endif // AABB_H

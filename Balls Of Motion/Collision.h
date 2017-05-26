#ifndef COLLISION_H
#define COLLISION_H

#include <GL/glut.h>
#include "Extra.h"

#include "AABB.h"
#include "Sphere.h"

/// Returns the minimum distance between to two objects
float distanceSA(Sphere* s, AABB* ab);
/// Returns the minimum distance between to two objects
float distanceSS(Sphere* s1, Sphere* s2);

/// Returns true when the two objects are colliding
int collidesSA(Sphere* s, AABB* ab);
/// Returns true when the two objects are colliding
int collidesSS(Sphere* s1, Sphere* s2);

/// Calculates the distance between the two points
float distance(vect3 p1, vect3 p2);

/** Reflect a sphere against a normal
 * e.g. Reflect off of a wall
 */
void reflectS(Sphere* s, vect3 normal);

/** /brief Resolves a collision between a aabb and a sphere
 * The sphere is moved to the closest valid location outside of the AABB
 * and its direction is reflected
 */
void resolveSA(Sphere* s, AABB* aabb);

/** Resolve a collision between 2 spheres
 * See: http://ericleong.me/research/circle-circle/#dynamic-circle-circle-collision
 */
void resolveSS(Sphere* s1, Sphere* s2);

#endif // COLLISION_H

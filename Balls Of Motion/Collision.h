#ifndef COLLISION_H
#define COLLISION_H

#include <GL/glut.h>
#include "Extra.h"

#include "AABB.h"
#include "Sphere.h"

int distanceSA(Sphere* s, AABB* ab);
int distanceSS(Sphere* s1, Sphere* s2);

int collidesSA(Sphere* s, AABB* ab);
int collidesSS(Sphere* s1, Sphere* s2);

float distance(vect3 p1, vect3 p2);

/** Reflect a sphere against a normal
 * e.g. Reflect off of a wall
 */
//TODO: void reflectS(Sphere* s, vect3 normal);

/** Resolve a collision between 2 spheres
 * See: http://ericleong.me/research/circle-circle/#dynamic-circle-circle-collision
 */
//TODO: void resolveSS(Sphere* s1, Sphere* s2);

#endif // COLLISION_H

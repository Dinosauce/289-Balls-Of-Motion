#ifndef COLLISION_H
#define COLLISION_H

#include <GL/glut.h>
#include "Extra.h"

#include "AABB.h"
#include "Sphere.h"

int CollidesSA(Sphere* s, AABB* ab);
int CollidesSS(Sphere* s1, Sphere* s2);

float Distance(vect3 p1, vect3 p2);

#endif // COLLISION_H

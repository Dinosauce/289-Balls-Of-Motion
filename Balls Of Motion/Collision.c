#include "Collision.h"

int CollidesSA(Sphere* s, AABB* ab)
{
    vect3 point;

    Clamp(ab, s->center, point);

    return Distance(point, s->center) < s->radius;
}

int CollidesSS(Sphere* s1, Sphere* s2)
{
    return Distance(s1->center, s2->center) < (s1->radius + s2->radius);
}

float Distance(vect3 p1, vect3 p2)
{
    float x, y, z;

    x = p1[0] - p2[0];
    y = p1[1] - p2[1];
    z = p1[2] - p2[2];

    return (float) sqrt(x*x + y*y + z*z);
}

#include "Collision.h"

int collidesSA(Sphere* s, AABB* ab)
{
    vect3 point;

    clamp(ab, s->center, point);

    return distance(point, s->center) < s->radius;
}

int collidesSS(Sphere* s1, Sphere* s2)
{
    return distance(s1->center, s2->center) < (s1->radius + s2->radius);
}

float distance(vect3 p1, vect3 p2)
{
    float x, y, z;

    x = p1[0] - p2[0];
    y = p1[1] - p2[1];
    z = p1[2] - p2[2];

    return (float) sqrt(x*x + y*y + z*z);
}

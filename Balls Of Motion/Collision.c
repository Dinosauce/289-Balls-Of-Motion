#include "Collision.h"


float distanceSA(Sphere* s, AABB* ab)
{
    vect3 point;

    clamp(ab, s->center, point);

    return (distance(point, s->center) - s->radius);
}
float distanceSS(Sphere* s1, Sphere* s2)
{
    return distance(s1->center, s2->center) - (s1->radius + s2->radius);
}


int collidesSA(Sphere* s, AABB* ab)
{
    return distanceSA(s, ab) < 0;
}

int collidesSS(Sphere* s1, Sphere* s2)
{
    return distanceSS(s1, s2) < 0;
}

//TODO: Separate reflect from sphere (reflect should be a function taking two vectors)
void reflectS(Sphere* s, vect3 normal)
{
    reflect(s->direction, normal);
}

void resolveSA(Sphere* s, AABB* aabb)
{
    vect3 point;

    clamp(aabb, s->center, point);

    int i;
    for (i = 0; i < 3; i++)
    {
        // Only works when the circles center is still outside the aabb
        s->center[i] = point[i] + (aabb->normal[i] * s->radius);
    }

    reflectS(s, aabb->normal);
}

void resolveSS(Sphere* s1, Sphere* s2)
{
    float d = distance(s1->center, s2->center);
    vect3 n; // x,y and z normal (from s2 -> s1)
    int i;

    // Sets the collision normal
    for (i = 0; i< 3; i++)
    {
        n[i] = (s2->center[i] - s1->center[i]) / d;
    }

    // calculate p-value
    float p = 2 * (dot(s1->direction, n) - dot(s2->direction, n)) / (s1->mass + s2->mass);

    // Calculate / set new velocity for each sphere
    for (i = 0; i< 3; i++)
    {
        s1->direction[i] = s1->direction[i] - (p * s1->mass * n[i]);
        s2->direction[i] = s2->direction[i] + (p * s2->mass * n[i]);
    }
}

float distance(vect3 p1, vect3 p2)
{
    float x, y, z;

    x = p1[0] - p2[0];
    y = p1[1] - p2[1];
    z = p1[2] - p2[2];
    return (float) sqrt(x*x + y*y + z*z);
}

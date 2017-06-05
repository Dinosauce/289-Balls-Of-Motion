#include "Sphere.h"

void setSphere(Sphere* newSphere, float x, float y, float z, float radius)
{
    newSphere->center[0] = x;
    newSphere->center[1] = y;
    newSphere->center[2] = z;

    newSphere->radius = radius;

    newSphere->direction[0] = 0;
    newSphere->direction[1] = 0;
    newSphere->direction[2] = 0;

    newSphere->mass = 1;
}

void setSphereVelocity(Sphere* sphere, float xv, float yv, float zv)
{
    sphere->direction[0] = xv;
    sphere->direction[1] = yv;
    sphere->direction[2] = zv;
}

void setSphereMass(Sphere* sphere, float m)
{
    sphere->mass = m;
}

void animate(Sphere* s, float gravity, int tick)
{
    float time = tick / 1000.0;

    s->direction[1] -= gravity * time;

    s->center[0] += s->direction[0] * time;
    s->center[1] += s->direction[1] * time;
    s->center[2] += s->direction[2] * time;
}

void drawSphere(Sphere* s)
{
    glPushMatrix();
        glTranslatef(s->center[0], s->center[1], s->center[2]);
        glScaled(s->radius, s->radius, s->radius);
        glutSolidSphere(1, 30, 30);
    glPopMatrix();

}

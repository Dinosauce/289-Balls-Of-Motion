#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include "Extra.h"

typedef struct{
    vect3 center;
    vect3 direction;
    float radius;
} Sphere;

    /** Initializes a sphere
     *
     * \param newSphere - sphere to initialize
     * \param x - center of sphere
     * \param y - center of sphere
     * \param z - center of sphere
     * \param radius - radius of the sphere
     */
    void setSphere(Sphere* newSphere, float x, float y, float z, float radius);

    void animate(Sphere* s, int tick);

    void drawSphere(Sphere* s);

    //void drawSphere(int slices);

#endif // SPHERE_H

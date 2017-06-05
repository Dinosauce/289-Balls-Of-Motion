#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glut.h>
#include "Extra.h"

/// \author Jayden Grant

/// Defines a sphere with velocity (direction) and mass
typedef struct{
    vect3 center;
    vect3 direction;
    float radius;
    float mass;
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

    /// Sets the spheres velocity in x, y, and z directions
    void setSphereVelocity(Sphere* sphere, float xv, float yv, float zv);

    /// Sets the spheres mass
    void setSphereMass(Sphere* sphere, float mass);

    /** Updates the spheres position based on its direction and the
      * tick (time passed since last update)
      */
    void animate(Sphere* s, float gravity, int tick);

    /// Renders the sphere
    void drawSphere(Sphere* s);

#endif // SPHERE_H

#ifndef EXTRA_H
#define EXTRA_H


#include <math.h>
    const static float RADIAN_MULT = M_PI/180;

    /// Definces a point in 3D space.
    typedef float vect3[3];

    typedef vect3 vert4[4];

	float clampF(float min, float max, float point);

#endif // EXTRA_H

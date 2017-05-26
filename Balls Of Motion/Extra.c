#include "Extra.h"

float clampF(float min, float max, float point)
{
    if (point < min)
        point = min;
    else if (point > max)
        point = max;

    return point;
}

float dot(vect3 v1, vect3 v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void normalize(vect3 vector)
{
    float mag = vector[0] * vector[0] +
                    vector[1] * vector[1] +
                    vector[2] * vector[2];

    if (mag == 1)
        return;
    else
    {
        float sqr = sqrt(mag);
        int i;
        for (i = 0; i < 3; i++)
            vector[i] /= sqr;
    }
}

void reflect(vect3 vec, vect3 normal)
{
    vect3 reflection;
    int i;

    normalize(normal);

    float d = dot(vec, normal);

    for (i = 0; i < 3; i++)
    {
        reflection[i] = -2 * d * normal[i] + vec[i];
    }

    for (i = 0; i < 3; i++)
    {
        vec[i] = reflection[i];
    }
}

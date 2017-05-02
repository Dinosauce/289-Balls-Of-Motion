#include "Extra.h"

float clampF(float min, float max, float point)
{
    if (point < min)
        point = min;
    else if (point > max)
        point = max;

    return point;
}

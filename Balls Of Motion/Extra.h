#ifndef EXTRA_H
#define EXTRA_H


#include <math.h>
    const static float RADIAN_MULT = M_PI/180;

    /// Definces a point in 3D space.
    typedef float vect3[3];

    /// 3x4 Matrix
    typedef vect3 vert4[4];

    /** /brief Returns the point clamped between min and max.
     * If the point is between the two points the point in returned.
     * /param min - the minimum point to clamp to
     * /param max - the max point to clamp to
     * /param point - the point to clamp
     * /return the clamped point
     */
	float clampF(float min, float max, float point);

	/// Normailizes the given vector
	void normalize(vect3 vector);

	/// Reflects the vector against the normal
	void reflect(vect3 vec, vect3 normal);

	/// Returns the dot product of the two vectors
	float dot(vect3 v1, vect3 v2);

	/// Returns 1 when the two vectors are equal (0 otherwise)
	int equals(vect3 v1, vect3 v2);
#endif // EXTRA_H

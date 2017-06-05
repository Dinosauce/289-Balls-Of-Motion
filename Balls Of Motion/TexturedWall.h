#ifndef TEXWALL_H
#define TEXWALL_H

#include <GL/glut.h>
#include "Extra.h"

typedef enum { xAxis, yAxis, zAxis} axis;//, xNAxis, yNAxis, zNAxis }axis;

/**
 * Container for an axis aligned surface.
 * \note when pos is the minimum point on the surface, its normal is in the positive direction,
 *  if pos is the maximum point, its normal is in the negative direction.
 *  \author Jayden Grant
 */
typedef struct
{
    vect3 pos;
    float length; // x for floor
    float height; // z for floor
    axis type;

    vect3 color;
    GLuint texId;

    float texVertRes;
    float lenRatio;
} TexturedWall;

/**
 * @param pos - position of the wall to extend from.
 * @param xSize - length to extend in positive x axis
 * @param zSize - length to extend in positive z axis
 */
void setFloor(TexturedWall* wall, float x, float y, float z, float xSize, float zSize);

/**
 * @param pos - position of bottom of the wall, extends in positive direction of length.
 * @param length - length to extend along perpendicular axis direction
 * @param height - height of wall in positive y direction
 * @param direction - the axis along which to extend the wall.
 */
void setWall(TexturedWall* wall, float x, float y, float z, float length, float height, axis direction);

/// Sets the color of the wall (Disables textures)
void setWallColor(TexturedWall* wall, float r, float g, float b);

/** Sets the texture Id and properties for the wall, enabling textures.
 *  @param wall - wall to apply changes to.
 *  @param textureID - the texture ID of texture already loaded into openGL
 *  @param verticleRep - the number of times to repeat the texture in the vertical direction (floor: x)
 *  @param lengthRatio - length to height ratio to apply to texture repetition (floor: x to z ratio)
 */
void setWallTexture(TexturedWall* wall, GLuint textureID, float verticleRep, float lengthRatio);

/// Draws the wall using GL
void drawWall(TexturedWall* wall);

#endif // TEXWALL_H

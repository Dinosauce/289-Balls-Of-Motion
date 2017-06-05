#include "TexturedWall.h"

void setFloor(TexturedWall* wall, float x, float y, float z, float xSize, float zSize)
{
    wall->pos[0] = x;
    wall->pos[1] = y;
    wall->pos[2] = z;

    wall->length = xSize;
    wall->height = zSize;
    wall->type = yAxis;

    wall->texId = 0;
    wall->texVertRes = 1;
    wall->lenRatio = 1;

    setWallColor(wall, 1, 0 ,1);
}

void setWall(TexturedWall* wall, float x, float y, float z, float length, float height, axis direction)
{
//    if (direction == yAxis || direction == yNAxis)
//        setFloor(wall, x, y, z, length, height, direction);
//    else

    wall->pos[0] = x;
    wall->pos[1] = y;
    wall->pos[2] = z;

    wall->length = length;
    wall->height = height;
    wall->type = direction;

    wall->texId = 0;
    wall->texVertRes = 1;
    wall->lenRatio = 1;

    setWallColor(wall, 1, 1 ,1);
}

void setWallTexture(TexturedWall* wall, GLuint textureID, float verticleRep, float lengthRatio)
{
    wall->texId = textureID;
    wall->texVertRes = verticleRep;
    wall->lenRatio = lengthRatio;
}

void setWallColor(TexturedWall* wall, float r, float g, float b)
{
    wall->texId = 0;

    wall->color[0] = r;
    wall->color[1] = g;
    wall->color[2] = b;
}

void drawWall(TexturedWall* wall)
{
    if (wall->texId == 0)
        glColor3f(wall->color[0], wall->color[1], wall->color[2]);
    else
    {


        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, wall->texId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

        glColor3f(1,1,1);
    }

    switch(wall->type)
    {
        case yAxis:
            glBegin(GL_POLYGON);
                    glTexCoord2f(0,0);
                glVertex3f(wall->pos[0], wall->pos[1], wall->pos[2]);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio,0);
                glVertex3f(wall->pos[0], wall->pos[1], wall->pos[2] + wall->height);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio, wall->texVertRes);
                glVertex3f(wall->pos[0] + wall->length, wall->pos[1], wall->pos[2] + wall->height);
                    glTexCoord2f(0, wall->texVertRes);
                glVertex3f(wall->pos[0] + wall->length, wall->pos[1], wall->pos[2]);
            glEnd();
          break;
        case xAxis:
            glBegin(GL_POLYGON);
                    glTexCoord2f(0,0);
                glVertex3f(wall->pos[0], wall->pos[1], wall->pos[2]);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio,0);
                glVertex3f(wall->pos[0] + wall->length, wall->pos[1], wall->pos[2]);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio, wall->texVertRes);
                glVertex3f(wall->pos[0] + wall->length, wall->pos[1] + wall->height, wall->pos[2]);
                    glTexCoord2f(0, wall->texVertRes);
                glVertex3f(wall->pos[0], wall->pos[1] + wall->height, wall->pos[2]);
            glEnd();
          break;
        case zAxis:
            glBegin(GL_POLYGON);
                    glTexCoord2f(0,0);
                glVertex3f(wall->pos[0], wall->pos[1], wall->pos[2]);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio,0);
                glVertex3f(wall->pos[0], wall->pos[1], wall->pos[2] + wall->length);
                    glTexCoord2f(wall->texVertRes * wall->lenRatio, wall->texVertRes);
                glVertex3f(wall->pos[0], wall->pos[1] + wall->height, wall->pos[2] + wall->length);
                    glTexCoord2f(0, wall->texVertRes);
                glVertex3f(wall->pos[0], wall->pos[1] + wall->height, wall->pos[2]);
            glEnd();
          break;
    }// end switch
    glDisable(GL_TEXTURE_2D);
}

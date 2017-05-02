#include "Sphere.h"

void setSphere(Sphere* newSphere, float x, float y, float z, float radius)
{
    newSphere->center[0] = x;
    newSphere->center[1] = y;
    newSphere->center[2] = z;

    newSphere->direction[0] = 1.0f;
    newSphere->direction[1] = 0.0f;
    newSphere->direction[2] = 0.0f;

    newSphere->radius = radius;
}

void animate(Sphere* s, int tick)
{
    float time = tick / 1000.0;
    s->center[0] += s->direction[0] * time;
    s->center[1] += s->direction[1] * time;
    s->center[2] += s->direction[2] * time;
}

//TODO: Rewrite, dont need to recreate sphere every frame
void draw()
{
    int slices = 20;

    float vAng, hAng;
    float vD = 160.0 / slices;
    float hD = 360.0 / slices;

    //glColor3f(0.0, 0.0, 0.0);

    float point = 10.0 * RADIAN_MULT;
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, 1.0, 0.0);
        for(hAng = 0.0; hAng <= (360.0); hAng += hD)
        {
            //glColor3f(10.0/160.0, hAng / 360.0, 10.0/160.0);
            glVertex3f(sin((hAng) * RADIAN_MULT) * sin(point),
                           cos(point),
                           cos((hAng) * RADIAN_MULT) * sin(point));
        }
    glEnd();

    for(vAng = 10.0; vAng <= (170.0 - vD); vAng += vD)
    {
        float point = vAng * RADIAN_MULT;
        float point2 = (vAng + vD) * RADIAN_MULT;

        for(hAng = 0.0; hAng <= (360.0 - hD); hAng += hD)
        {
            //glColor3f(vAng/160.0, hAng / 360.0, vAng/160.0);
            glBegin(GL_POLYGON);
                glVertex3f(sin((hAng) * RADIAN_MULT) * sin(point),
                           cos(point),
                           cos((hAng) * RADIAN_MULT) * sin(point));

                glVertex3f(sin((hAng + hD) * RADIAN_MULT) * sin(point),
                           cos(point),
                           cos((hAng + hD) * RADIAN_MULT) * sin(point));

                glVertex3f(sin((hAng + hD) * RADIAN_MULT) * sin(point2),
                           cos(point2),
                           cos((hAng + hD) * RADIAN_MULT) * sin(point2));

                glVertex3f(sin((hAng) * RADIAN_MULT) * sin(point2),
                           cos(point2),
                           cos((hAng) * RADIAN_MULT) * sin(point2));
            glEnd();
        }
    }

    point = vAng * RADIAN_MULT;
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, -1.0, 0.0);
        for(hAng = 0.0; hAng <= (360.0); hAng += hD)
        {
            //glColor3f(vAng/160.0, hAng / 360.0, vAng/160.0);
            glVertex3f(sin((hAng) * RADIAN_MULT) * sin(point),
                           cos(point),
                           cos((hAng) * RADIAN_MULT) * sin(point));
        }
    glEnd();
}

void drawSphere(Sphere* s)
{
    glPushMatrix();
        glTranslatef(s->center[0], s->center[1], s->center[2]);
        glScaled(s->radius, s->radius, s->radius);
        draw();
    glPopMatrix();

}


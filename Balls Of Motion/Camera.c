#include "Camera.h"

void setCam(Camera* newCam, double x, double y, double z, double maxViewAngle)
{
    //Set cam position
    newCam->cPos[0] = x;
    newCam->cPos[1] = y;
    newCam->cPos[2] = z;

    //Set cam viewing vector
    newCam->cCen[0] = newCam->cPos[0];
    newCam->cCen[1] = newCam->cPos[1];
    newCam->cCen[2] = newCam->cPos[2] - 1.0;

    //Set cams normals
    newCam->cNorm[0] = 0.0;
    newCam->cNorm[1] = 1.0;
    newCam->cNorm[2] = 0.0;

    //Set default move and rotate speeds.
    newCam->moveSpeed = 0.2;
    newCam->rotateSpeed = 0.05;

    //Initialize cameras current z, and y viewing angles.
    newCam->yRad = 0.0;
    newCam->zRad = 0.0;

    newCam->yVel = 0;

    //Prevent Camera from looking
    if (maxViewAngle > 89.9 || maxViewAngle < 0.0)
        maxViewAngle = 89.9;

    //Set maximum y viewing angle.
    newCam->maxYRad = maxViewAngle * RADIAN_MULT;
}

void moveCam(Camera* cam, double forwardVel, double sideVel)
{

    if (cam->cPos[1] <= 1.7)
    {
        cam->cPos[1] = 1.7;
        cam->yVel =0;
    }
    else
    {
        cam->yVel -= 0.03;
    }
    if ((cam->cPos[1] += cam->yVel) < 1.7)
        cam->cPos[1] = 1.7;

    if (forwardVel == 0 || sideVel == 0)
    {
        moveForward(cam, forwardVel);
        moveSide(cam, sideVel);
    }
    else //Movement is diagonal, so speed is normalized.
    {
        moveForward(cam, forwardVel * cos(45 * RADIAN_MULT));
        moveSide(cam, sideVel * cos(45 * RADIAN_MULT));
    }

}

void moveForward(Camera* cam, double vel)
{
    cam->cPos[0] += (cam->moveSpeed * vel *  sin(cam->zRad));
    cam->cPos[2] += (cam->moveSpeed * vel * -cos(cam->zRad));

    cam->cCen[0] = cam->cPos[0] + (sin(cam->zRad) * cos(cam->yRad));
    cam->cCen[2] = cam->cPos[2] - (cos(cam->zRad) * cos(cam->yRad));
    cam->cCen[1] = cam->cPos[1] + sin(cam->yRad);
}

void moveSide(Camera* cam, double vel)
{
    cam->cPos[0] += (cam->moveSpeed * vel *  sin(cam->zRad + RADIAN_MULT * 90.0));
    cam->cPos[2] += (cam->moveSpeed * vel * -cos(cam->zRad + RADIAN_MULT * 90.0));

    cam->cCen[0] = cam->cPos[0] + (sin(cam->zRad) * cos(cam->yRad));
    cam->cCen[2] = cam->cPos[2] - (cos(cam->zRad) * cos(cam->yRad));
    cam->cCen[1] = cam->cPos[1] + sin(cam->yRad);
}

void rotateCameraZ(Camera* cam, double vel)
{
    cam->zRad += cam->rotateSpeed * vel;
}

void rotateCameraY(Camera* cam, double vel)
{
    if ((cam->yRad + (cam->rotateSpeed * vel)) >= cam->maxYRad)
    {
        cam->yRad = cam->maxYRad;
    }
    else if ((cam->yRad + (cam->rotateSpeed * vel)) <= -(cam->maxYRad))
    {
        cam->yRad = -(cam->maxYRad);
    }
    else
    {
        cam->yRad += cam->rotateSpeed * vel;
    }
}

void adjustMovespeed(Camera* cam, double dSpeed)
{
    cam->moveSpeed += dSpeed;
}

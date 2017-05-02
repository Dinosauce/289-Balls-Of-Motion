#ifndef CAMERA_H
#define CAMERA_H

#include "Extra.h"

    /// Container for a single camera.
    typedef struct
    {
        vect3 cPos;     // Camera's position
        vect3 cCen;     // Camera's line of sight vector
        vect3 cNorm;    // Camera's normals

        double yVel;

        double moveSpeed;       // Camera's movement speed.
        double rotateSpeed;     // Camera's rotate speed

        double yRad, zRad;      // Camera's current vertical and horizontal viewing angle.
        double maxYRad;         // Camera's maximum vertical viewing angle.
    }Camera;

    /** \brief Sets the default values for a given camera.
     *
     * \param newCam (Camera*) - The camera to set
     * \param x (double) - Starting x position.
     * \param y (double) - Starting y position.
     * \param z (double) - Starting z position.
     * \param maxViewAngle (double) - The maximum vertical viewing angle.
     */
    void setCam(Camera* newCam, double x, double y, double z, double maxViewAngle);

    /** \brief Moves the given camera's position, normalizes speed.
     *
     * \param cam (Camera*) - The camera to move
     * \param forwardVel (double) - The velocity to move the camera in the direction it is facing (x,z).
     * \param sideVel (double) - The velocity to move the camera perpendicular to the direction it is facing (x,z).
     */
    void moveCam(Camera* cam, double forwardVel, double sideVel);

    /** \brief Moves the given camera's position forwards.
     *
     * \param cam (Camera*) - The camera to move.
     * \param vel (double) - The velocity to move the camera in the direction it is facing (x,z).
     */
    void moveForward(Camera* cam, double vel);

    /** \brief Moves the given camera's position sideways.
     *
     * \param cam (Camera*) - The camera to move.
     * \param vel (double) - The velocity to move the camera perpendicular to the direction it is facing (x,z).
     */
    void moveSide(Camera* cam, double vel);

    /** \brief Rotates the horizontal direction the camera is facing.
     *
     * \param  cam (Camera*) - The camera to move.
     * \param  vel (double) - The direction and magnitude to rotate the camera in.
     */
    void rotateCameraZ(Camera* cam, double vel);

    /** \brief Rotates the vertical direction the camera is facing.
     *
     * \param  cam (Camera*) - The camera to move.
     * \param  vel (double) - The direction and magnitude to rotate the camera in.
     */
    void rotateCameraY(Camera* cam, double vel);

    /** \brief Increases the camera's move speed by the given value.
     *
     * \param cam (Camera*) - The camera to adjust.
     * \param dSpeed - The amount to change the camera speed by.
     */
    void adjustMovespeed(Camera* cam, double dSpeed);

#endif // CAMERA_H

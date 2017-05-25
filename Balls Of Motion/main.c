#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>

#include "Camera.h"
//#include "Sphere.h"
#include "Collision.h"
#include "Windows.h"


Camera cam;
Sphere s;
Sphere s2;

double test = 0.0;

int forward = 0;       //Forward movement velocity.
int backward = 0;
int left = 0;     //Sidewards movement velocity.
int right = 0;


int zRotate = 0;    //Z-Axiz rotation velocity.
int yRotate = 0;    //Y-Axiz rotation velocity.

int mouseFunc = 0;  //Determines whether the mouse is in control of the camera.

int windowWidth = 1280;  //Windows width
int windowHeight = 720; //Windows height
int windowXcen;         //Windows horizontal center
int windowYcen;         //Windows vertical center
int mouseX;             //Mouses current x position relative to windows.
int mouseY;             //Mouses current y position relative to windows.

typedef GLfloat GLpoint3[3];

const int FRAMEDELAY = 1000/60.0f;   //Minimum delay between frames in milliseconds.

int lastUpdate;

void drawSphere2(int slices)
{
    //float points[slices][slices];

    double h, r, hd, rd;
    hd = 180/slices;
    rd = 360/slices;

    for (h = 10; h <= 170; h += hd)
    {
        glBegin(GL_LINE_LOOP);
        for (r = 0; r < 360; r += rd)
        {
            double wt = sin((M_PI/180)* h);
            glVertex3d(wt * sin(RADIAN_MULT * r), cos(RADIAN_MULT * h), wt * cos(RADIAN_MULT * r));
        }
        glEnd();
    }
}

void myinit()
{
    ///Init =========================
    //setLight();
    glClearColor(0.8, 0.9, 1.0, 1.0); /* draw on white background */
    glEnable(GL_DEPTH_TEST);
    setCam(&cam, 0.0, 1.7, 10.0, 75.0);
    setSphere(&s, 0.0f, 1.0f, 1.0f, 1.0f);
    setSphere(&s2, 0.0, 0.0, 1.0, 2.0);
    /// =============================
}

void setLight()
{
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {10.0};

    GLfloat position[] = {0.0, 2.5, 10.0, 0.0};
    GLfloat ambience[] = {0.5, 0.5, 0.5, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambience);

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void mouseMove(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

void toggleMouse()
{
    mouseFunc = !mouseFunc;

    if (mouseFunc)
    {
        glutWarpPointer(windowXcen, windowYcen);
        glutPassiveMotionFunc(mouseMove);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else
    {
        glutPassiveMotionFunc(NULL);
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

void drawHouse()
{

    GLpoint3 house[8] = {
        {-2.0, 0.0, 3.0},
        {2.0, 0.0, 3.0},
        {-2.0, 2.4, 3.0},
        {2.0, 2.4, 3.0},
        {-2.0, 2.4, -3.0},
        {2.0, 2.4, -3.0},
        {-2.0, 0.0, -3.0},
        {2.0, 0.0, -3.0}
    };

    //z plane far / near
    glColor3d(0.0, 1.0, 0.5);
    glBegin(GL_POLYGON);
        glVertex3fv(house[0]);
        glVertex3fv(house[1]);
        glVertex3fv(house[3]);
        glVertex3fv(house[2]);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(house[4]);
        glVertex3fv(house[5]);
        glVertex3fv(house[7]);
        glVertex3fv(house[6]);
    glEnd();

    //roof / floor
    glColor3d(1.0, 0.7, 0.3);
    glBegin(GL_POLYGON);
        glVertex3fv(house[2]);
        glVertex3fv(house[3]);
        glVertex3fv(house[5]);
        glVertex3fv(house[4]);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(house[6]);
        glVertex3fv(house[7]);
        glVertex3fv(house[1]);
        glVertex3fv(house[0]);
    glEnd();

    //raised roof
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 4.0f, 0.0f);
        glVertex3fv(house[2]);
        glVertex3fv(house[3]);
        glVertex3fv(house[5]);
        glVertex3fv(house[4]);
        glVertex3fv(house[2]);
    glEnd();

    //x plane near / far
    glColor3d(0.5, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex3fv(house[1]);
        glVertex3fv(house[7]);
        glVertex3fv(house[5]);
        glVertex3fv(house[3]);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3fv(house[6]);
        glVertex3fv(house[0]);
        glVertex3fv(house[2]);
        glVertex3fv(house[4]);
    glEnd();
}

void keyPress(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'd':
    case 'D':
        right = 1;
        break;
    case 'a':
    case 'A':
        left = 1;
        break;

    case 'w':
    case 'W':
        forward = 1;
        break;
    case 's':
    case 'S':
        backward = 1;
        break;
    case ' ':
        if (cam.cPos[1] <= 1.7)
        {
            cam.yVel = 0.3;
            cam.cPos[1] += 0.00001;
        }
        break;
    case ';':
        test += 0.1;
        break;
    }
}

void keyRelease(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'd':
    case 'D':
        right = 0;
        break;
    case 'a':
    case 'A':
        left = 0;
        break;

    case 'w':
    case 'W':
        forward = 0;
        break;
    case 's':
    case 'S':
        backward = 0;
        break;
    case 'r':
    case 'R':
        toggleMouse();
        break;
    case 27:
        exit(0);
    }
}

void specKeyPress(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        yRotate = 1;
        break;
    case GLUT_KEY_DOWN:
        yRotate = -1;
        break;

    case GLUT_KEY_LEFT:
        zRotate = -1;
        break;
    case GLUT_KEY_RIGHT:
        zRotate = 1;
        break;
    }
}

void specKeyRelease(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        yRotate = 0;
        break;

    case GLUT_KEY_LEFT:
    case GLUT_KEY_RIGHT:
        zRotate = 0;
        break;
    }
}

// Must be called after glLoadIdentity() and before drawing in perspective.
void updateCamera()
{
    if (mouseFunc)
    {
        rotateCameraZ(&cam, (float) (mouseX - windowXcen) / 80.0);
        rotateCameraY(&cam, (float) (windowYcen - mouseY) / 80.0);

        glutWarpPointer(windowXcen, windowYcen);
    }
    else
    {
        rotateCameraZ(&cam, zRotate);
        rotateCameraY(&cam, yRotate);
    }

    moveCam(&cam, forward - backward, right - left);

    gluLookAt(cam.cPos[0], cam.cPos[1], cam.cPos[2],
              cam.cCen[0], cam.cCen[1], cam.cCen[2],
              cam.cNorm[0], cam.cNorm[1], cam.cNorm[2]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    updateCamera();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(10.0);

    glColor3d(1.0, 0.0, 1.0);
    drawSphere(&s);

    glPushMatrix();
        glTranslated(-3.0, 0.0, 0.0);
        drawHouse();
    glPopMatrix();

    glPushMatrix();
        glTranslated(4.0, 0.0, 0.0);
        glRotated(90.0, 0.0, 1.0, 0.0);
        drawHouse();
    glPopMatrix();


    glPushMatrix();
        glColor3f(1.0, 0.2, 0.0);
        glTranslated(0.0, 1.6, 0.0);
        drawSphere2(15);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.95, 0.9, 0.15);
        glTranslated(0.0, 1.5, 0.0);
        glScalef(0.12, 0.2, 0.12);
        drawSphere(&s);
    glPopMatrix();

    glutSwapBuffers();

    //glutTimerFunc(FRAMEDELAY, display, 0);
    //glutPostRedisplay();
}

void frameCheck()
{
    glutTimerFunc(FRAMEDELAY, frameCheck, 0);
    animate(&s, glutGet(GLUT_ELAPSED_TIME) - lastUpdate);
    lastUpdate = glutGet(GLUT_ELAPSED_TIME);
    display();
}

void resize(int x, int y)
{
    if (y == 0)
        y = 1;

    windowHeight = y;
    windowWidth = x;
    windowXcen = windowWidth / 2;
    windowYcen = windowHeight / 2;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);
    gluPerspective(90, windowWidth*1.0/windowHeight, 0.01, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow("OFF Loader Test");

    myinit();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutSpecialFunc(specKeyPress);
    glutSpecialUpFunc(specKeyRelease);

    lastUpdate = glutGet(GLUT_ELAPSED_TIME);
    frameCheck();

    glutMainLoop();

    return 0;
}
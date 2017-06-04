#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glut.h>

#include "Camera.h"
#include "Collision.h"
#include "Windows.h"
#include "Extra.h"
#include "RawLoader.h"
#include "TexturedWall.h"


Camera cam;
Sphere camCollider;
#define NUM_AABB  6
#define NUM_SPHERE 5
AABB* aabbList;
Sphere* sphereList;

#define NUM_WALLS 6
TexturedWall* wallList;

// ====== Image overlays
int showMenu = 1;
int showExit = 0;
//Tex Ids
GLuint texMenu, texExit;
GLuint texWall, texFloor;

// ====== Movement
int forward = 0;       //Forward movement velocity.
int backward = 0;
int left = 0;     //Sidewards movement velocity.
int right = 0;

// ====== Ball spawn variables
float velocity = 5;
float mass = 1;
float gravity = 9.8f;
float radius = 1;
float energyLoss = 0.9;


// ====== Camera movement
int zRotate = 0;    //Z-Axiz rotation velocity.
int yRotate = 0;    //Y-Axiz rotation velocity.

int mouseFunc = 0;  //Determines whether the mouse is in control of the camera.

// ====== Window
int windowWidth = 1280;  //Windows width
int windowHeight = 720; //Windows height
int windowXcen;         //Windows horizontal center
int windowYcen;         //Windows vertical center
int mouseX;             //Mouses current x position relative to windows.
int mouseY;             //Mouses current y position relative to windows.

typedef GLfloat GLpoint3[3];

const int FRAMEDELAY = 1000/60.0f;   //Minimum delay between frames in milliseconds.

// Initialize game and openGL
void myinit()
{
    ///Init =========================
    //setLight();
    glClearColor(0.8, 0.9, 1.0, 1.0); /* draw on white background */
    glEnable(GL_DEPTH_TEST);
    setCam(&cam, 0.0, 1.7, 10.0, 75.0);
    setSphere(&camCollider, cam.cPos[0], cam.cPos[1], cam.cPos[2], 0.3);

    // Load Images
    image img;
    img.data = loadRaw("Content/Exit.raw", 640, 640);
    img.width = 640;
    img.height = 640;
    allocateImage(&img, &texExit);
    free(img.data);

    img.data = loadRaw("Content/Help.raw", 640, 640);
    allocateImage(&img, &texMenu);
    free(img.data);

    img.width = 128;
    img.height = 128;
    img.data = loadRaw("Content/BRICK.raw", 128, 128);
    allocateImage(&img, &texWall);
    free(img.data);

    img.data = loadRaw("Content/FLOOR.raw", 128, 128);
    allocateImage(&img, &texFloor);
    free(img.data);



    wallList = malloc(NUM_WALLS * (sizeof(*wallList)));
    setWall(&wallList[0], -16, 0, -12, 32, 9.6, xAxis);
    setWall(&wallList[1], -16, 0, -12, 24, 9.6, zAxis);

    setWall(&wallList[2], 16, 9.6, 12, -32, -9.6, xAxis);
    setWall(&wallList[3], 16, 9.6, 12, -24, -9.6, zAxis);

    setFloor(&wallList[4], -16, 0, -12, 32, 24);
    setFloor(&wallList[5], 16, 9.6, 12, -32, -24);
    int tx;
    for (tx = 0; tx < 4; tx ++)
        setTexture(&wallList[tx], texWall, 5, (wallList[tx].length / wallList[tx].height) );
    for (tx = 4; tx < 6; tx ++)
        setTexture(&wallList[tx], texFloor, 5, 2.0f);//(wallList[tx].length / wallList[tx].height) );
    //Set House Walls
    // -16 - 16
    // 0   - 9.6
    // -12 - 12
    aabbList = malloc(NUM_AABB * (sizeof(*aabbList)));

    setAABB(&aabbList[0],-18, 0, -12, -16, 9.6, 12);
    setNormal(&aabbList[0], 1, 0, 0);
    setAABB(&aabbList[1],16, 0, -12, 18, 9.6, 12);
    setNormal(&aabbList[1], -1, 0, 0);

    setAABB(&aabbList[2],-16, -2, -12, 16, 0, 12);
    setNormal(&aabbList[2], 0, 1, 0);
    setAABB(&aabbList[3],-16, 9.6, -12, 16, 11.6, 12);
    setNormal(&aabbList[3], 0, -1, 0);

    setAABB(&aabbList[4],-16, 0, -14, 16, 9.6, -12);
    setNormal(&aabbList[4], 0, 0, 1);
    setAABB(&aabbList[5],-16, 0, 12, 16, 9.6, 14);
    setNormal(&aabbList[5], 0, 0, -1);

    // Initialize Test Spheres
    sphereList = malloc(NUM_SPHERE * (sizeof(*sphereList)));

    setSphere(&sphereList[0], -10.0f, 1.6f, 1.0f, 1.0f);
    setSphereVelocity(&sphereList[0], 8, 0, 0);
    setSphereMass(&sphereList[0], 20);

    setSphere(&sphereList[1], 0.0, 1.6f, 1.0f, 1.0f);
    setSphereVelocity(&sphereList[1], 1, 0, 0);
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
    case 9: // Horizontal tab
    case 'i':
    case 'I':
        // If statement ensures mouse is visible when game isn't running
        if (!showExit)  // Dont toggle menu/help when on exit screen
        {
            showMenu = !showMenu;
            toggleMouse();
        }
        break;
    case 27:
    case 'Q':
    case 'q':
        // If statement ensures mouse is visible when game isn't running
        if (showMenu) // Allow exit when in menu/help
            showExit = !showExit;
        else
        {
            showExit = !showExit;
            toggleMouse();
        }
        break;
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

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //Exit or left click when exit screen is shown
        if(showExit)
            exit(0);
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

    // Update camera collider
    int i;
    for (i = 0; i < 3; i++)
                    camCollider.center[i] = cam.cPos[i];
}

// (Crude) Displays the string at x, y screen using glut bitmap
void rendText(char* str, int len, int x, int y)
{
    glTranslatef(x, y, 0);

    //Set Bottom Right Raster Position
    glRasterPos2d(0, 0);
    int i;
    for (i = 0; str[i] != '\0' && i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

}

// Displays game variables
void displayText()
{
        // Set 2D display
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);
    gluOrtho2D(0.0, windowWidth, windowHeight, 0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, 0);
    // Text colour white
    glColor3f(1,1,1);

    const int len = 32;
    int height = 24;
    char txt[32] = {0};

    strcpy(txt, "Gravity: ");
    rendText(txt, len, 0, height);
    sprintf(txt, "%.2f\0", gravity);
    rendText(txt, len, 0, height);

    strcpy(txt, "Initial Mass: ");
    rendText(txt, len, 0, height);
    sprintf(txt, "%.2f\0", mass);
    rendText(txt, len, 0, height);

    strcpy(txt, "Initial Velocity: ");
    rendText(txt, len, 0, height);
    sprintf(txt, "%.2f\0", velocity);
    rendText(txt, len, 0, height);

    strcpy(txt, "Initial Radius: ");
    rendText(txt, len, 0, height);
    sprintf(txt, "%.2f\0", radius);
    rendText(txt, len, 0, height);
}

//Displays a square image, centered in the window (stretched)
void showImage(GLuint texID)
{
    // Set 2D display
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);
    gluOrtho2D(0.0, windowWidth, windowHeight, 0);

    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Reset color to display fill texture colors
    glColor3f(1,1,1);

    //Fit image to the screen
    if (windowWidth > windowHeight)
        displayImage(texID, (windowWidth - windowHeight)/2, 0, windowHeight, windowHeight);
    else
        displayImage(texID, 0, (windowHeight - windowWidth)/2, windowWidth, windowWidth);

    glutSwapBuffers();
}

void display()
{
    // Reset 3D drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, windowWidth, windowHeight);
    gluPerspective(90, windowWidth*1.0/windowHeight, 0.01, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Disable textures
    glBindTexture(GL_TEXTURE_2D, 0);

    updateCamera();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glLineWidth(10.0);


    //TODO: Give each individual sphere a color. Random on spawn??? (if not textured)
    glColor3d(0.2, 0.5, 1.0);
    int s;
    for (s=0; s<NUM_SPHERE; s++)
    {
        drawSphere(&sphereList[s]);
    }

    glPushMatrix();
        //glScalef(8,4,4);
        //drawHouse();
        int w;
        for (w=0; w<NUM_WALLS; w++)
        {
            drawWall(&wallList[w]);
        }
    glPopMatrix();

    displayText();

    glutSwapBuffers();
}

void updateGame(int time)
{
    int a, s, j, i;
    for (s=0; s<NUM_SPHERE; s++)
    {
        animate(&sphereList[s], gravity, time);
    }

    //Check for collision with walls
    for (a=0; a< NUM_AABB; a++)
    {
        // Check collision on camera
        if(collidesSA(&camCollider, &aabbList[a]))
        {
                resolveSA(&camCollider, &aabbList[a]);
                for (i = 0; i < 3; i++)
                    cam.cPos[i] = camCollider.center[i];
        }

        for (s=0; s<NUM_SPHERE; s++)
        {
            if(collidesSA(&sphereList[s], &aabbList[a]))
            {
                resolveSA(&sphereList[s], &aabbList[a]);
                multiply(&sphereList[s].direction, energyLoss);
            }
        }
    }

    for (s = 0; s < NUM_SPHERE; s++)
    {
        for (j = s + 1; j < NUM_SPHERE; j++)
        {
            if(collidesSS(&sphereList[s], &sphereList[j]))
            {
                resolveSS(&sphereList[s], &sphereList[j]);
                //multiply(&sphereList[s].direction, energyLoss);
                //multiply(&sphereList[j].direction, energyLoss);
            }
        }
    }
}

void frameCheck()
{
    // glut will call frameCheck as soon as possible but AFTER FRAMEDELAY has passed.
    // This means the game will attempt to run at the specified framerate, or slower if it cannot
    // keep up.
    // This will cause the animation to slow down.
    glutTimerFunc(FRAMEDELAY, frameCheck, 0);

    if (!showExit)
    {
        if (!showMenu)
        {
            updateGame(FRAMEDELAY);
            display();
        }
        else { showImage(texMenu); }
    }
    else { showImage(texExit); }
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

    glutMouseFunc(mouseClick);

    frameCheck();

    //glutFullScreen();

    glutMainLoop();

    return 0;
}

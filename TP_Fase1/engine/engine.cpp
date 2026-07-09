#define _USE_MATH_DEFINES
#include <math.h>
#include "config/config.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

Config conf;
GLenum mode = GL_LINE;

float camX, camY, camZ;
float lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;
float alpha = 0.0f, beta = 0.0f, radius = 5.0f;
float fov = 45.0f, near = 1.0f, far = 1000.0f;

float red = 1.0f;
float green = 1.0f;
float blue = 1.0f;

// Spherical to Cartesian coordinates
void cartesianCoords()
{
    camX = radius * cos(beta) * sin(alpha);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alpha);
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(fov, ratio, near, far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawAxis(void)
{
    glBegin(GL_LINES);
    // X Axis
    glColor3f(RED);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis
    glColor3f(GREEN);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis
    glColor3f(BLUE);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void drawModels(Config *conf)
{
    for (auto it : conf->models)
    {
        glColor3f(red, green, blue);
        glBegin(GL_TRIANGLES);
        for (auto point : it.second)
        {
            glVertex3f(point.px, point.py, point.pz);
        }
        glEnd();
    }
}

void renderScene(void)
{
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
              lookX, lookY, lookZ,
              upX, upY, upZ);

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    drawAxis();

    drawModels(&conf);

    // End of frame
    glutSwapBuffers();
}

void menu(int op)
{
    switch (op)
    {
    case 0:
        mode = GL_FILL;
        break;
    case 1:
        mode = GL_LINE;
        break;
    case 2:
        mode = GL_POINT;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void processKeys(unsigned char c, int xx, int yy)
{
    // put code to process regular keys in here
    switch (c)
    {
    case 'w':
        radius -= 0.1f;
        if (radius < 0.1f)
            radius = 0.1f;
        break;
    case 's':
        radius += 0.1f;
        break;
    // Red
    case '0':
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
        break;
    // Green
    case '1':
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
        break;
    // Blue
    case '2':
        red = 0.0f;
        green = 0.0f;
        blue = 1.0f;
        break;
    // Yellow
    case '3':
        red = 1.0f;
        green = 1.0f;
        blue = 0.0f;
        break;
    // Orange
    case '4':
        red = 1.0f;
        green = 0.5f;
        blue = 0.0f;
        break;
    // Purple
    case '5':
        red = 1.0f;
        green = 0.0f;
        blue = 1.0f;
        break;
    // Cyan
    case '6':
        red = 0.0f;
        green = 1.0f;
        blue = 1.0f;
        break;
    // White
    case '7':
        red = 1.0f;
        green = 1.0f;
        blue = 1.0f;
        break;
    default:
        break;
    }
    cartesianCoords();
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy)
{
    // put code to process special keys in here
    switch (key)
    {
    case GLUT_KEY_UP:
        beta += 0.1f;
        if (beta > 1.5f)
            beta = 1.5f;
        break;
    case GLUT_KEY_DOWN:
        beta -= 0.1f;
        if (beta < -1.5f)
            beta = -1.5f;
        break;
    case GLUT_KEY_LEFT:
        alpha += 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        alpha -= 0.1f;
        break;
    }
    cartesianCoords();
    glutPostRedisplay();
}

void printInfo()
{
    cout << "------------------------------------------------------------" << endl;
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Use Arrows to move the camera up/down and left/right" << endl;
    cout << "W and S control the distance from the camera to the origin" << endl;
    cout << "Right click mouse to change drawing mode between FILL, LINE and POINT" << endl;
    cout << "To change primitives color, press numbers in range 0 - 7:" << endl;
    cout << "RED: 0" << endl;
    cout << "GREEN: 1" << endl;
    cout << "BLUE: 2" << endl;
    cout << "YELLOW: 3" << endl;
    cout << "ORANGE: 4" << endl;
    cout << "PURPLE: 5" << endl;
    cout << "CYAN: 6" << endl;
    cout << "WHITE: 7 (DEFAULT)" << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Not enough arguments" << endl;
        cout << "Use: ./generator <filename>" << endl;
        return 0;
    }
    // Load configuration
    int res = xmlToConfig(&conf, argv[1]);
    if (res > 0)
        return 0;
    // Position
    camX = conf.position[0];
    camY = conf.position[1];
    camZ = conf.position[2];
    // LookAt
    lookX = conf.lookAt[0];
    lookY = conf.lookAt[1];
    lookZ = conf.lookAt[2];
    // Up
    upX = conf.up[0];
    upY = conf.up[1];
    upZ = conf.up[2];
    // Projection
    fov = conf.projection[0];
    near = conf.projection[1];
    far = conf.projection[2];

    // radius = distance from (camX, camY, camZ) to (0, 0, 0)
    radius = sqrt(pow(camX, 2) + pow(camY, 2) + pow(camZ, 2));
    // camY = radius * sin(beta) -> beta = arcsen(camY / radius);
    beta = asin(camY / radius);
    // camZ = radius * cos(beta) * cos(alpha) -> acos(camZ / (radius * cos(beta)))
    alpha = acos(camZ / (radius * cos(beta)));

    !res && (cout << "Configuration loaded with success." << endl);

    for (auto it : conf.models)
    {
        int success = loadModelVertex(&conf, it.first);
        !success && (cout << it.first << " loaded with success." << endl);
    }

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(conf.window[0], conf.window[1]);
    glutCreateWindow("TP_FASE_1@CG");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // Create menus to change drawing mode
    glutCreateMenu(menu);
    glutAddMenuEntry("FILL", 0);
    glutAddMenuEntry("LINE", 1);
    glutAddMenuEntry("POINT", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Print app instructions and information
    printInfo();

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}

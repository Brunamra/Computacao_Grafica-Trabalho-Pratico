#include <stdio.h>
#include "config/config.h"
#include "utils/utils.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
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

float viewDirection[3] = {0.0f, 0.0f, 0.0f};
int cameraMode = 0;

int timebase;
float frames;
float startTime;

GLuint *buffers;
vector<GLuint> buffersSize;
int nModels = 0;

float previousY[3] = {0, 1, 0};

// Allows to rotate camera
void cameraOrientation()
{
    lookX = camX + cos(beta) * sin(alpha);
    lookY = camY + sin(beta);
    lookZ = camZ + cos(beta) * cos(alpha);
}

void getDirection()
{
    viewDirection[0] = lookX - camX;
    viewDirection[1] = lookY - camY;
    viewDirection[2] = lookZ - camZ;
}

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
    glVertex3f(-200.0f, 0.0f, 0.0f);
    glVertex3f(200.0f, 0.0f, 0.0f);
    // Y Axis
    glColor3f(GREEN);
    glVertex3f(0.0f, -200.0f, 0.0f);
    glVertex3f(0.0f, 200.0f, 0.0f);
    // Z Axis
    glColor3f(BLUE);
    glVertex3f(0.0f, 0.0f, -200.0f);
    glVertex3f(0.0f, 0.0f, 200.0f);
    glEnd();
}

void renderCatmullRomCurve(vector<vector<float>> controlPoints)
{
    // draw curve using line segments with GL_LINE_LOOP
    float res[3];
    float deriv[3];
    float t1 = 100.0f;

    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < t1; i += 1)
    {
        getGlobalCatmullRomPoint(i / t1, controlPoints, res, deriv);
        glVertex3f(res[0], res[1], res[2]);
    }

    glEnd();
}

void modelsToBuffers(Config *conf, Group group, int *bufferIndex)
{
    vector<string> models = group.models;
    if (!models.empty())
    {
        for (vector<string>::iterator model = models.begin(); model != models.end(); model++)
        {
            vector<float> bufferPoints;
            vector<Point> points = conf->models[*model];
            for (auto point : points)
            {
                bufferPoints.push_back(point.px);
                bufferPoints.push_back(point.py);
                bufferPoints.push_back(point.pz);
            }
            buffersSize.push_back(bufferPoints.size() / 3);

            glBindBuffer(GL_ARRAY_BUFFER, buffers[(*bufferIndex)++]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferPoints.size(), bufferPoints.data(), GL_STATIC_DRAW);
        }
    }
    vector<Group> groups = group.groups;
    if (!groups.empty())
    {
        for (vector<Group>::iterator it = groups.begin(); it != groups.end(); it++)
        {
            modelsToBuffers(conf, *it, bufferIndex);
        }
    }
}

void drawModelsVBO(Config *conf, Group group, int *index)
{
    glPushMatrix();
    vector<Transform> trans = group.transforms;
    if (!trans.empty())
    {
        for (vector<Transform>::iterator it = trans.begin(); it != trans.end(); it++)
        {
            int type = it->type;
            float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
            switch (type)
            {
            case 0:
                if (it->time > 0 && it->points.size() > 3)
                {
                    float t = (currentTime - startTime) / 1000.0 / it->time;
                    vector<vector<float>> controlPoints = pointsToFloats(it->points);

                    renderCatmullRomCurve(controlPoints);

                    // apply transformations here
                    float pos[3], deriv[3];
                    getGlobalCatmullRomPoint(t, controlPoints, pos, deriv);

                    glTranslatef(pos[0], pos[1], pos[2]);

                    if (it->align)
                    {
                        float xi[3] = {0, 0, 0};
                        xi[0] = deriv[0];
                        xi[1] = deriv[1];
                        xi[2] = deriv[2];
                        normalize(xi);

                        float zi[3] = {0, 0, 0};
                        cross(xi, previousY, zi);
                        normalize(zi);

                        float yi[3] = {0, 0, 0};
                        cross(zi, xi, yi);
                        normalize(yi);

                        previousY[0] = yi[0];
                        previousY[1] = yi[1];
                        previousY[2] = yi[2];

                        float m[16];
                        buildRotMatrix(xi, yi, zi, m);
                        glMultMatrixf(m);
                    }
                }
                else
                {
                    glTranslatef(it->coords.px, it->coords.py, it->coords.pz);
                }
                break;
            case 1:
                if (it->time > 0)
                {
                    it->angle = (currentTime - startTime) * 360.0 / 1000.0 / it->time;
                }
                glRotatef(it->angle, it->coords.px, it->coords.py, it->coords.pz);
                break;
            case 2:
                glScalef(it->coords.px, it->coords.py, it->coords.pz);
                break;
            default:
                break;
            }
        }
    }
    vector<string> models = group.models;
    if (!models.empty())
    {
        for (vector<string>::iterator it = models.begin(); it != models.end(); it++)
        {
            if ((*index) < nModels)
            {
                glColor3f(red, green, blue);
                glBindBuffer(GL_ARRAY_BUFFER, buffers[*index]);
                glVertexPointer(3, GL_FLOAT, 0, 0);
                glDrawArrays(GL_TRIANGLES, 0, buffersSize[*index]);
            }
            (*index)++;
        }
    }
    vector<Group> groups = group.groups;
    if (!groups.empty())
    {
        for (vector<Group>::iterator it = groups.begin(); it != groups.end(); it++)
        {
            drawModelsVBO(conf, *it, index);
        }
    }

    glPopMatrix();
}

void renderScene(void)
{
    float fps;
    int time;
    char s[64];

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    if (cameraMode == 1)
        cameraOrientation();

    gluLookAt(camX, camY, camZ,
              lookX, lookY, lookZ,
              upX, upY, upZ);

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    drawAxis();

    // drawModels(&conf, conf.group);
    int index = 0;
    drawModelsVBO(&conf, conf.group, &index);

    frames++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000)
    {
        fps = frames * 1000.0 / (time - timebase);
        timebase = time;
        frames = 0;
        sprintf(s, "TP_FASE_3@CG - FPS: %.3f - TIME: %d", fps, timebase / 1000);
        glutSetWindowTitle(s);
    }
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
    float speed = 0.5f;
    float r[3];
    float up[3] = {0.0f, 1.0f, 0.0f};
    // put code to process regular keys in here
    switch (c)
    {
    case 'w':
        if (cameraMode == 1)
        {
            getDirection();
            normalize(viewDirection);
            camX += speed * viewDirection[0];
            camY += speed * viewDirection[1];
            camZ += speed * viewDirection[2];

            lookX += speed * viewDirection[0];
            lookY += speed * viewDirection[1];
            lookZ += speed * viewDirection[2];
            break;
        }
        else
        {
            radius -= 0.1f;
            if (radius < 0.1f)
                radius = 0.1f;
            break;
        }
    case 's':
        if (cameraMode == 1)
        {
            getDirection();
            normalize(viewDirection);
            camX -= speed * viewDirection[0];
            camY -= speed * viewDirection[1];
            camZ -= speed * viewDirection[2];

            lookX -= speed * viewDirection[0];
            lookY -= speed * viewDirection[1];
            lookZ -= speed * viewDirection[2];
            break;
        }
        else
        {
            radius += 0.1f;
            break;
        }
    case 'a':
        if (cameraMode == 1)
        {
            r[0] = 0.0f;
            r[1] = 0.0f;
            r[2] = 0.0f;

            getDirection();
            normalize(viewDirection);

            cross(viewDirection, up, r);
            normalize(r);

            camX -= speed * r[0];
            camY -= speed * r[1];
            camZ -= speed * r[2];

            lookX -= speed * r[0];
            lookY -= speed * r[1];
            lookZ -= speed * r[2];
        }
        break;
    case 'd':
        if (cameraMode == 1)
        {
            r[0] = 0.0f;
            r[1] = 0.0f;
            r[2] = 0.0f;

            getDirection();
            normalize(viewDirection);

            cross(viewDirection, up, r);
            normalize(r);

            camX += speed * r[0];
            camY += speed * r[1];
            camZ += speed * r[2];

            lookX += speed * r[0];
            lookY += speed * r[1];
            lookZ += speed * r[2];
        }
        break;
    case 'e':
        if (cameraMode == 1)
        {
            cameraMode = 0;
            lookX = 0;
            lookY = 0;
            lookZ = 0;
            cartesianCoords();
        }
        break;
    case 'f':
        if (cameraMode == 0)
        {
            cameraMode = 1;
            camX = -camX;
            camY = 1.0f;
            camZ = -camZ;

            cameraOrientation();
        }
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
    if (cameraMode == 0)
    {
        cartesianCoords();
    }
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
    if (cameraMode == 1)
    {
        cameraOrientation();
    }
    else
    {
        cartesianCoords();
    }
    glutPostRedisplay();
}

void printInfo()
{
    cout << "------------------------------------------------------------" << endl;
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "Camera mode:" << endl;
    cout << "- press E for Exlorer Mode Camera (DEFAULT)" << endl;
    cout << "- press F for FPS Camera" << endl;
    cout << "Use Arrows and W, S, A, D to move the camera up/down and left/right" << endl;
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

    // Get number of models to draw
    modelsCount(conf.group, &nModels);
    // Allocate memory for buffers
    buffers = (GLuint *)malloc(sizeof(GLuint) * nModels);

    // DEBUG
    // printGroup(conf.group);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(conf.window[0], conf.window[1]);
    glutCreateWindow("TP_FASE_3@CG");

    timebase = glutGet(GLUT_ELAPSED_TIME);
    startTime = (float)glutGet(GLUT_ELAPSED_TIME);

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // Create menus to change drawing mode
    glutCreateMenu(menu);
    glutAddMenuEntry("FILL", 0);
    glutAddMenuEntry("LINE", 1);
    glutAddMenuEntry("POINT", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // init GLEW
#ifndef __APPLE__
    glewInit();
#endif

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create buffers
    glGenBuffers(nModels, buffers);

    // Load information to buffers
    int buffersIndex = 0;
    modelsToBuffers(&conf, conf.group, &buffersIndex);

    // Print app instructions and information
    printInfo();

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}

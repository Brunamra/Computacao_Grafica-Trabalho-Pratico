#include <stdio.h>
#include "config/config.h"
#include "utils/utils.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include </usr/local/include/IL/il.h>

#define WHITE 1.0f, 1.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0f, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f

Config conf;
GLenum mode = GL_FILL;

float camX, camY, camZ;
float lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f;
float upX = 0.0f, upY = 1.0f, upZ = 0.0f;
float alpha = 0.0f, beta = 0.0f, radius = 5.0f;
float fov = 45.0f, near = 1.0f, far = 1000.0f;

float viewDirection[3] = {0.0f, 0.0f, 0.0f};
int cameraMode = 0;

int timebase;
float frames;
float startTime;

GLuint *buffers, *nBuffers, *texBuffers, *texIDs;
vector<GLuint> buffersSize, nBuffersSize;
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
    glDisable(GL_LIGHTING);

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

    glEnable(GL_LIGHTING);
}

int loadTexture(std::string textureFile, int *bufferIndex)
{
    unsigned int t, tw, th;
    unsigned char *texData;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ILboolean openFileSuccess = ilLoadImage((ILstring)textureFile.c_str());
    if (openFileSuccess == IL_FALSE)
    {
        cout << "Something went wrong trying to open " << textureFile << "." << endl;
        return 1;
    }
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texIDs[(*bufferIndex)]);

    glBindTexture(GL_TEXTURE_2D, texIDs[(*bufferIndex)]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;
}

void renderCatmullRomCurve(vector<vector<float> > controlPoints)
{
    // draw curve using line segments with GL_LINE_LOOP
    float res[3];
    float deriv[3];
    float t1 = 100.0f;

    // glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < t1; i += 1)
    {
        getGlobalCatmullRomPoint(i / t1, controlPoints, res, deriv);
        glVertex3f(res[0], res[1], res[2]);
    }

    glEnd();
    // glEnable(GL_LIGHTING);
}

void modelsToBuffers(Config *conf, Group group, int *bufferIndex)
{
    vector<ModelSettings> models = group.models;
    if (!models.empty())
    {
        for (vector<ModelSettings>::iterator model = models.begin(); model != models.end(); model++)
        {
            vector<float> bufferPoints;
            vector<Point> points = conf->models[model->modelFile].vertices;
            vector<float> bufferNormals;
            vector<Point> normals = conf->models[model->modelFile].normals;
            vector<float> bufferTextures;
            vector<TexCoord> textures = conf->models[model->modelFile].texCoords;

            for (auto point : points)
            {
                bufferPoints.push_back(point.px);
                bufferPoints.push_back(point.py);
                bufferPoints.push_back(point.pz);
            }
            buffersSize.push_back(bufferPoints.size() / 3);

            for (auto normal : normals)
            {
                bufferNormals.push_back(normal.px);
                bufferNormals.push_back(normal.py);
                bufferNormals.push_back(normal.pz);
            }
            nBuffersSize.push_back(bufferNormals.size() / 3);

            for (auto texture : textures)
            {
                bufferTextures.push_back(texture.x);
                bufferTextures.push_back(texture.y);
            }

            glBindBuffer(GL_ARRAY_BUFFER, buffers[(*bufferIndex)]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferPoints.size(), bufferPoints.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, nBuffers[(*bufferIndex)]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferNormals.size(), bufferNormals.data(), GL_STATIC_DRAW);

            if (!textures.empty())
            {
                glBindBuffer(GL_ARRAY_BUFFER, texBuffers[(*bufferIndex)]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferTextures.size(), bufferTextures.data(), GL_STATIC_DRAW);
                loadTexture(model->textureFile, bufferIndex);
            }

            (*bufferIndex)++;
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
                    vector<vector<float> > controlPoints = pointsToFloats(it->points);

                    renderCatmullRomCurve(controlPoints);

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
    vector<ModelSettings> models = group.models;
    if (!models.empty())
    {
        for (vector<ModelSettings>::iterator it = models.begin(); it != models.end(); it++)
        {
            if ((*index) < nModels)
            {
                glMaterialfv(GL_FRONT, GL_AMBIENT, it->color.ambient);
                glMaterialfv(GL_FRONT, GL_SPECULAR, it->color.specular);
                glMaterialfv(GL_FRONT, GL_EMISSION, it->color.emissive);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, it->color.diffuse);
                glMaterialf(GL_FRONT, GL_SHININESS, it->color.shininess);

                if (!it->textureFile.empty())
                {
                    glBindBuffer(GL_ARRAY_BUFFER, texBuffers[*index]);
                    glTexCoordPointer(2, GL_FLOAT, 0, 0);
                    glBindTexture(GL_TEXTURE_2D, texIDs[*index]);
                }

                glBindBuffer(GL_ARRAY_BUFFER, nBuffers[*index]);
                glNormalPointer(GL_FLOAT, 0, 0);

                glBindBuffer(GL_ARRAY_BUFFER, buffers[*index]);
                glVertexPointer(3, GL_FLOAT, 0, 0);

                glDrawArrays(GL_TRIANGLES, 0, buffersSize[*index]);

                // Unbind textures
                if (!it->textureFile.empty())
                {
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
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

GLenum getLight(int i)
{
    switch (i)
    {
    case 0:
        return GL_LIGHT0;
    case 1:
        return GL_LIGHT1;
    case 2:
        return GL_LIGHT2;
    case 3:
        return GL_LIGHT3;
    case 4:
        return GL_LIGHT4;
    case 5:
        return GL_LIGHT5;
    case 6:
        return GL_LIGHT6;
    case 7:
        return GL_LIGHT7;
    default:
        return -1;
    }
}

void activateLights(Config *conf)
{
    vector<Light> lights = conf->lights;
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float global_light_amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    if (!lights.empty())
    {
        for (int i = 0; i < lights.size(); i++)
        {
            switch (lights[i].type)
            {
            case 0:
                glLightfv(getLight(i), GL_POSITION, lights[i].pos);
                break;
            case 1:
                normalize(lights[i].dir);
                glLightfv(getLight(i), GL_POSITION, lights[i].dir);
                break;
            case 2:
                glLightfv(getLight(i), GL_POSITION, lights[i].pos);
                normalize(lights[i].dir);
                glLightfv(getLight(i), GL_SPOT_DIRECTION, lights[i].dir);
                glLightf(getLight(i), GL_SPOT_CUTOFF, lights[i].cuttOff);
                glLightf(getLight(i), GL_SPOT_EXPONENT, 0.0);
                break;
            default:
                break;
            }
            glLightfv(getLight(i), GL_DIFFUSE, white);
            glLightfv(getLight(i), GL_SPECULAR, white);
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_light_amb);
    }
}

void renderScene(void)
{
    float fps;
    int time;
    char s[64];

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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

    activateLights(&conf);

    int index = 0;
    drawModelsVBO(&conf, conf.group, &index);

    frames++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 1000)
    {
        fps = frames * 1000.0 / (time - timebase);
        timebase = time;
        frames = 0;
        sprintf(s, "TP_FASE_4@CG - FPS: %.3f - TIME: %d", fps, timebase / 1000);
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
    float speed = 1.0f;
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
            cout << "Current camera mode: Explorer" << endl;

            radius = sqrt(pow(camX, 2) + pow(camY, 2) + pow(camZ, 2));
            beta = asin(camY / radius);
            alpha = (camX < 0 ? -1.0f : 1.0f) * acos(camZ / (radius * cos(beta)));

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
            cout << "Current camera mode: FPS" << endl;

            // Adjust angles to get the correct view direction
            beta = -beta;
            alpha = M_PI + alpha;
            cameraOrientation();
        }
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
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Not enough arguments" << endl;
        cout << "Use: ./engine <filename>" << endl;
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
    // Check where camX is to avoid jumps
    // camZ = radius * cos(beta) * cos(alpha) -> acos(camZ / (radius * cos(beta)))
    alpha = (camX < 0 ? -1.0f : 1.0f) * acos(camZ / (radius * cos(beta)));

    !res && (cout << "Configuration loaded with success." << endl);

    for (auto it : conf.models)
    {
        int success = loadModelVertex(&conf, it.first);
        !success && (cout << it.first << " loaded with success." << endl);
    }

    // DEBUG
    // printGroup(conf.group);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(conf.window[0], conf.window[1]);
    glutCreateWindow("TP_FASE_4@CG");

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
    glPolygonMode(GL_FRONT, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    timebase = glutGet(GLUT_ELAPSED_TIME);
    startTime = (float)glutGet(GLUT_ELAPSED_TIME);

    // Enable lights
    vector<Light> lights = conf.lights;
    if (!lights.empty() && lights.size() < 9)
    {
        for (int i = 0; i < lights.size(); i++)
        {
            glEnable(getLight(i));
        }
    }

    // Get number of models to draw
    modelsCount(conf.group, &nModels);

    // Allocate memory for buffers
    buffers = (GLuint *)malloc(sizeof(GLuint) * nModels);
    nBuffers = (GLuint *)malloc(sizeof(GLuint) * nModels);
    texBuffers = (GLuint *)malloc(sizeof(GLuint) * nModels);
    // Array of textures IDs
    texIDs = (GLuint *)malloc(sizeof(GLuint) * nModels);

    // Create buffers
    glGenBuffers(nModels, buffers);
    glGenBuffers(nModels, nBuffers);
    glGenBuffers(nModels, texBuffers);

    // Load information to buffers
    int buffersIndex = 0;
    modelsToBuffers(&conf, conf.group, &buffersIndex);

    // Print app instructions and information
    printInfo();

    // enter GLUT's main cycle
    glutMainLoop();

    // Clear buffers
    free(buffers);
    free(nBuffers);
    free(texBuffers);
    free(texIDs);
    return 1;
}

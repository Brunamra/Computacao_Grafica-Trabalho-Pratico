#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "../tinyxml2/tinyxml2.h"

using std::cout;
using std::endl;
using std::map;
using std::pair;
using std::string;
using std::vector;

using namespace tinyxml2;

struct Point
{
    float px, py, pz;
};

struct TexCoord
{
    float x, y;
};

// Transform type
// 0 - Translate
// 1 - Rotate
// 2 - Scale
// Transform align
// 0 - false
// 1 - true
struct Transform
{
    int type;
    float angle;
    Point coords;
    float time = 0;
    int align = 0;
    vector<Point> points;
};

struct Color
{
    float diffuse[3] = {200.0f, 200.0f, 200.0f};
    float ambient[3] = {50.0f, 50.0f, 50.0f};
    float specular[3] = {0.0f, 0.0f, 0.0f};
    float emissive[3] = {0.0f, 0.0f, 0.0f};
    float shininess = 0.0f;
};

// Light type
// 0 - point
// 1 - directional
// 2 - spotlight
struct Light
{
    int type;
    float pos[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float dir[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float cuttOff;
};

struct ModelSettings
{
    string modelFile;
    string textureFile;
    Color color;
};

struct ModelInfo
{
    vector<Point> vertices;
    vector<Point> normals;
    vector<TexCoord> texCoords;
};

struct Group
{
    vector<Transform> transforms;
    vector<ModelSettings> models;
    vector<Group> groups;
};

struct Config
{
    int window[2];
    float position[3];
    float lookAt[3];
    float up[3];
    float projection[3];
    vector<Light> lights;
    map<string, ModelInfo> models;
    Group group;
};

int xmlToConfig(Config *conf, string xmlFile);
int addToWindow(Config *conf, int width = 512, int height = 512);
int addToPosition(Config *conf, float x, float y, float z);
int addToLookAt(Config *conf, float x, float y, float z);
int addToUp(Config *conf, float x, float y, float z);
int addToProjection(Config *conf, float fov, float near, float far);
int addToModels(Config *conf, string model);
int loadModelVertex(Config *conf, string model);
Group addGroup(XMLElement *element, Config *conf);
void printGroup(Group group);
int modelsCount(Group group, int *result);
vector<vector<float> > pointsToFloats(vector<Point> controlPoints);

#endif
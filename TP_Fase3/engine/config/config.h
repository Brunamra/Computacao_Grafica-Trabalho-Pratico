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

struct Group
{
    vector<Transform> transforms;
    vector<string> models;
    vector<Group> groups;
};

struct Config
{
    int window[2];
    float position[3];
    float lookAt[3];
    float up[3];
    float projection[3];
    map<string, vector<Point>> models;
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
vector<vector<float>> pointsToFloats(vector<Point> controlPoints);

#endif
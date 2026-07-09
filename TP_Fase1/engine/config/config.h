#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include <string.h>
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

struct Config
{
    int window[2];
    float position[3];
    float lookAt[3];
    float up[3];
    float projection[3];
    map<string, vector<Point>> models;
};

int xmlToConfig(Config *conf, string xmlFile);
int addToWindow(Config *conf, int width = 512, int height = 512);
int addToPosition(Config *conf, float x, float y, float z);
int addToLookAt(Config *conf, float x, float y, float z);
int addToUp(Config *conf, float x, float y, float z);
int addToProjection(Config *conf, float fov, float near, float far);
int addToModels(Config *conf, string model);
int loadModelVertex(Config *conf, string model);

#endif
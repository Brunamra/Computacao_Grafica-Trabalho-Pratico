#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <fstream>
#include <iostream>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

using std::cout;
using std::endl;
using std::ofstream;

int createPlaneXZ(int lenght, int divisions, char *filename, int up = 0);
int createPlaneXY(int lenght, int divisions, char *filename, int up = 0);
int createPlaneYZ(int lenght, int divisions, char *filename, int up = 0);
int createBox(int lenght, int divisions, char *filename);
int createSphere(int radius, int slices, int stacks, char *filename);
int createCone(int radius, int height, int slices, int stacks, char *filename);

#endif
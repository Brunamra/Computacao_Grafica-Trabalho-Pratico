#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::vector;

int createPlaneXZ(int lenght, int divisions, char *filename, int up = 0);
int createPlaneXY(int lenght, int divisions, char *filename, int up = 0);
int createPlaneYZ(int lenght, int divisions, char *filename, int up = 0);
int createBox(int lenght, int divisions, char *filename);
int createSphere(int radius, int slices, int stacks, char *filename);
int createCone(int radius, int height, int slices, int stacks, char *filename);
int createRing(float innerRadius, float outerRadius, int slices, char *filename);
vector<vector<vector<float> > > loadPatch(char *filename);
int createPrimitive(vector<vector<vector<float> > > patchInfo, float tesselattion, char *destFilename);
void multiplyMatrix(float *m1, int m1Rows, int m1Columns, float *m2, int m2Rows, int m2Columns, float *resM);
void bezierSurfacePoint(float u, float v, vector<vector<float> > patch, float *point, float *normal);

#endif
#ifndef UTILS_H
#define UTILS_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

using std::vector;

void buildRotMatrix(float *x, float *y, float *z, float *m);
void normalize(float *a);
void cross(float *a, float *b, float *res);
float length(float *v);
void multMatrixVector(float *m, float *v, float *res);
void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
void getGlobalCatmullRomPoint(float gt, vector<vector<float> > controlPoints, float *pos, float *deriv);

#endif
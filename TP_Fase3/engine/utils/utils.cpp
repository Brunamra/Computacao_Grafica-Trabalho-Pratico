#include "utils.h"

void buildRotMatrix(float *x, float *y, float *z, float *m)
{
    m[0] = x[0];
    m[1] = x[1];
    m[2] = x[2];
    m[3] = 0;
    m[4] = y[0];
    m[5] = y[1];
    m[6] = y[2];
    m[7] = 0;
    m[8] = z[0];
    m[9] = z[1];
    m[10] = z[2];
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}

void cross(float *a, float *b, float *res)
{

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(float *a)
{

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

float length(float *v)
{

    float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return res;
}

void multMatrixVector(float *m, float *v, float *res)
{

    for (int j = 0; j < 4; ++j)
    {
        res[j] = 0;
        for (int k = 0; k < 4; ++k)
        {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void getCatmullRomPoint(float t, vector<float> p0, vector<float> p1, vector<float> p2, vector<float> p3, float *pos, float *deriv)
{

    float m[4][4] = {{-0.5f, 1.5f, -1.5f, 0.5f},
                     {1.0f, -2.5f, 2.0f, -0.5f},
                     {-0.5f, 0.0f, 0.5f, 0.0f},
                     {0.0f, 1.0f, 0.0f, 0.0f}};

    for (int i = 0; i < 3; i++)
    {
        float vectorA[4] = {0, 0, 0, 0};
        float vectorP[4] = {p0[i], p1[i], p2[i], p3[i]};

        multMatrixVector(*m, vectorP, vectorA);

        float vectorT[4] = {t * t * t, t * t, t, 1};
        float vectordT[4] = {3 * t * t, 2 * t, 1, 0};

        pos[i] = (vectorT[0] * vectorA[0]) + (vectorT[1] * vectorA[1]) + (vectorT[2] * vectorA[2]) + (vectorT[3] * vectorA[3]);
        deriv[i] = (vectordT[0] * vectorA[0]) + (vectordT[1] * vectorA[1]) + (vectordT[2] * vectorA[2]) + (vectordT[3] * vectorA[3]);
    }
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, vector<vector<float>> controlPoints, float *pos, float *deriv)
{
    int POINT_COUNT = controlPoints.size();
    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);       // which segment
    t = t - index;              // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
    indices[1] = (indices[0] + 1) % POINT_COUNT;
    indices[2] = (indices[1] + 1) % POINT_COUNT;
    indices[3] = (indices[2] + 1) % POINT_COUNT;

    getCatmullRomPoint(t, controlPoints[indices[0]], controlPoints[indices[1]], controlPoints[indices[2]], controlPoints[indices[3]], pos, deriv);
}

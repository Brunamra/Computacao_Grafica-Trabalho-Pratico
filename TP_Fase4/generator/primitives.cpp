#include "primitives.h"

string openFileError = "Something went wrong trying to open the file.";
string createFileSuccess = " created with success.";

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

int createPlaneXZ(int lenght, int divisions, char *filename, int front)
{
    ofstream plane;
    plane.open(filename, std::ios::out | std::ios::app);

    if (!plane)
    {
        cout << openFileError << endl;
        return 1;
    }

    float px, py, pz;
    float mid = (float)lenght / 2;
    // int nv = 6 * pow(divisions, 2);
    float increment = (float)lenght / (float)divisions;
    px = -mid;
    pz = -mid;
    py = (front == 0) ? 0 : mid;

    float texInc = 1.0f / (float)divisions;
    float texX, texY;
    // Y -> Z Axis
    texX = 0.0f;
    texY = 1.0f;

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << (px + increment) << " " << py << " " << (pz + increment) << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << (texX + texInc) << " " << (texY - texInc) << endl;
                plane << (px + increment) << " " << py << " " << pz << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << (texX + texInc) << " " << texY << endl;

                plane << (px + increment) << " " << py << " " << (pz + increment) << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << (texX + texInc) << " " << (texY - texInc) << endl;
                plane << px << " " << py << " " << pz << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << px << " " << py << " " << (pz + increment) << " "
                      << 0 << " " << 1 << " " << 0 << " "
                      << texX << " " << (texY - texInc) << endl;
            }
            else
            {
                plane << px << " " << -py << " " << pz << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << (px + increment) << " " << -py << " " << pz << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << (texX + texInc) << " " << texY << endl;
                plane << (px + increment) << " " << -py << " " << (pz + increment) << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << (texX + texInc) << " " << (texY - texInc) << endl;

                plane << (px + increment) << " " << -py << " " << (pz + increment) << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << (texX + texInc) << " " << (texY - texInc) << endl;
                plane << px << " " << -py << " " << (pz + increment) << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << texX << " " << (texY - texInc) << endl;
                plane << px << " " << -py << " " << pz << " "
                      << 0 << " " << -1 << " " << 0 << " "
                      << texX << " " << texY << endl;
            }
            px += increment;
            texX += texInc;
        }
        px = -mid;
        pz += increment;
        texX = 0;
        texY -= texInc;
    }
    plane.close();
    !front &&cout << filename << createFileSuccess << endl;

    return 0;
}

int createPlaneXY(int lenght, int divisions, char *filename, int front)
{
    ofstream plane;
    plane.open(filename, std::ios::out | std::ios::app);

    if (!plane)
    {
        cout << openFileError << endl;
        return 1;
    }

    float px, py, pz;
    float mid = (float)lenght / 2;
    // int nv = 6 * pow(divisions, 2);
    float increment = (float)lenght / (float)divisions;
    px = -mid;
    pz = (front == 0) ? 0 : mid;
    py = -mid;

    float texInc = 1.0f / (float)divisions;
    float texX, texY;
    texX = 0.0f;
    texY = 0.0f;

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << texX << " " << texY << endl;
                plane << (px + increment) << " " << py << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << (texX + texInc) << " " << texY << endl;
                plane << (px + increment) << " " << (py + increment) << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << (texX + texInc) << " " << (texY + texInc) << endl;

                plane << (px + increment) << " " << (py + increment) << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << (texX + texInc) << " " << (texY + texInc) << endl;
                plane << px << " " << (py + increment) << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << texX << " " << (texY + texInc) << endl;
                plane << px << " " << py << " " << pz << " "
                      << 0 << " " << 0 << " " << 1 << " "
                      << texX << " " << texY << endl;
            }
            else
            {
                plane << px << " " << py << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << texX << " " << texY << endl;
                plane << (px + increment) << " " << (py + increment) << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << (texX + texInc) << " " << (texY + texInc) << endl;
                plane << (px + increment) << " " << py << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << (texX + texInc) << " " << texY << endl;

                plane << (px + increment) << " " << (py + increment) << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << (texX + texInc) << " " << (texY + texInc) << endl;
                plane << px << " " << py << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << texX << " " << texY << endl;
                plane << px << " " << (py + increment) << " " << -pz << " "
                      << 0 << " " << 0 << " " << -1 << " "
                      << texX << " " << (texY + texInc) << endl;
            }
            px += increment;
            texX += texInc;
        }
        px = -mid;
        py += increment;
        texX = 0;
        texY += texInc;
    }
    plane.close();
    !front &&cout << "Plane XY created with success" << endl;
    return 0;
}

int createPlaneYZ(int lenght, int divisions, char *filename, int front)
{
    ofstream plane;
    plane.open(filename, std::ios::out | std::ios::app);

    if (!plane)
    {
        cout << openFileError << endl;
        return 1;
    }

    float px, py, pz;
    float mid = (float)lenght / 2;
    // int nv = 6 * pow(divisions, 2);
    float increment = (float)lenght / (float)divisions;
    px = (front == 0) ? 0 : mid;
    pz = -mid;
    py = -mid;

    float texInc = 1.0f / (float)divisions;
    float texX, texY;
    // X -> Z Axis
    texX = 1.0f;
    texY = 0.0f;

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << px << " " << (py + increment) << " " << (pz + increment) << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << (texY + texInc) << endl;
                plane << px << " " << py << " " << (pz + increment) << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << texY << endl;

                plane << px << " " << (py + increment) << " " << (pz + increment) << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << (texY + texInc) << endl;
                plane << px << " " << py << " " << pz << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << px << " " << (py + increment) << " " << pz << " "
                      << 1 << " " << 0 << " " << 0 << " "
                      << texX << " " << (texY + texInc) << endl;
            }
            else
            {
                plane << -px << " " << py << " " << pz << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << texX << " " << texY << endl;
                plane << -px << " " << py << " " << (pz + increment) << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << texY << endl;
                plane << -px << " " << (py + increment) << " " << (pz + increment) << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << (texY + texInc) << endl;

                plane << -px << " " << (py + increment) << " " << (pz + increment) << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << (texX - texInc) << " " << (texY + texInc) << endl;
                plane << -px << " " << (py + increment) << " " << pz << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << texX << " " << (texY + texInc) << endl;
                plane << -px << " " << py << " " << pz << " "
                      << -1 << " " << 0 << " " << 0 << " "
                      << texX << " " << texY << endl;
            }
            pz += increment;
            texX -= texInc;
        }
        pz = -mid;
        py += increment;
        texX = 1.0f;
        texY += texInc;
    }
    plane.close();
    !front &&cout << "Plane YZ created with success" << endl;
    return 0;
}

int createBox(int lenght, int divisions, char *filename)
{
    createPlaneXY(lenght, divisions, filename, 1);
    createPlaneXY(lenght, divisions, filename, -1);
    createPlaneYZ(lenght, divisions, filename, 1);
    createPlaneYZ(lenght, divisions, filename, -1);
    createPlaneXZ(lenght, divisions, filename, 1);
    createPlaneXZ(lenght, divisions, filename, -1);
    cout << filename << createFileSuccess << endl;
    return 0;
}

int createSphere(int radius, int slices, int stacks, char *filename)
{
    ofstream sphere;
    sphere.open(filename, std::ios::out | std::ios::trunc);

    if (!sphere)
    {
        cout << openFileError << endl;
        return 1;
    }

    float alpha, beta;

    float betaInc = M_PI / (float)stacks;
    float alphaInc = 2.0f * M_PI / (float)slices;
    float texX, texY, texXInc, texYInc;
    texX = texY = 0.0f;
    texXInc = 1.0f / (float)slices;
    texYInc = 1.0f / (float)stacks;

    for (int i = 0; i < stacks; i++)
    {
        beta = -(M_PI / 2.0f) + i * betaInc;
        texY = i * texXInc;

        for (int j = 0; j < slices; j++)
        {
            alpha = j * alphaInc;
            texX = j * texXInc;
            if (i == 0)
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << " " << cos(beta) * sin(alpha) << " " << sin(beta) << " " << cos(beta) * cos(alpha)
                       << " " << texX << " " << texY << endl;

                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << cos(beta + betaInc) * sin(alpha + alphaInc) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << (texY + texYInc) << endl;

                // top left
                sphere << radius * cos(beta + betaInc) * sin(alpha) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha)
                       << " " << cos(beta + betaInc) * sin(alpha) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha)
                       << " " << texX << " " << (texY + texYInc) << endl;
            }
            else if (i == stacks - 1)
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << " " << cos(beta) * sin(alpha) << " " << sin(beta) << " " << cos(beta) * cos(alpha)
                       << " " << texX << " " << texY << endl;
                // bottom right
                sphere << radius * cos(beta) * sin(alpha + alphaInc) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha + alphaInc)
                       << " " << cos(beta) * sin(alpha + alphaInc) << " " << sin(beta) << " " << cos(beta) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << texY << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << cos(beta + betaInc) * sin(alpha + alphaInc) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << (texY + texYInc) << endl;
            }
            else
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << " " << cos(beta) * sin(alpha) << " " << sin(beta) << " " << cos(beta) * cos(alpha)
                       << " " << texX << " " << texY << endl;
                // bottom right
                sphere << radius * cos(beta) * sin(alpha + alphaInc) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha + alphaInc)
                       << " " << cos(beta) * sin(alpha + alphaInc) << " " << sin(beta) << " " << cos(beta) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << texY << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << cos(beta + betaInc) * sin(alpha + alphaInc) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << (texY + texYInc) << endl;

                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << " " << cos(beta) * sin(alpha) << " " << sin(beta) << " " << cos(beta) * cos(alpha)
                       << " " << texX << " " << texY << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << cos(beta + betaInc) * sin(alpha + alphaInc) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha + alphaInc)
                       << " " << (texX + texXInc) << " " << (texY + texYInc) << endl;
                // top left
                sphere << radius * cos(beta + betaInc) * sin(alpha) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha)
                       << " " << cos(beta + betaInc) * sin(alpha) << " " << sin(beta + betaInc) << " " << cos(beta + betaInc) * cos(alpha)
                       << " " << texX << " " << (texY + texYInc) << endl;
            }
        }
    }
    sphere.close();
    cout << filename << createFileSuccess << endl;
    return 0;
}

int createCone(int radius, int height, int slices, int stacks, char *filename)
{
    ofstream cone;
    cone.open(filename, std::ios::out | std::ios::trunc);

    if (!cone)
    {
        cout << openFileError << endl;
        return 1;
    }

    float alphaInc = 2 * M_PI / (float)slices;
    float heightInc = height / (float)stacks;
    float radiusDec = (float)radius / (float)stacks;
    float currentHeight = 0;
    float currentRadius = 0;
    float texX, texY;
    texX = texY = 0.0f;

    float texXInc = 1.0f / (float)slices;
    float texYInc = 1.0f / (float)stacks;

    float beta = atan((float)radius / (float)height);
    float ny = sin(beta);

    float normal[3];

    // Draw Base
    for (int i = 0; i < slices; i++)
    {
        cone << cos(alphaInc * i) * radius << " " << 0 << " " << sin(alphaInc * i) * radius << " "
             << 0 << " " << -1 << " " << 0 << " "
             << 0.5f + 0.5f * cos(alphaInc * i) << " " << 0.5f + 0.5f * sin(alphaInc * i) << endl;

        cone << cos(alphaInc * (i + 1)) * radius << " " << 0 << " " << sin(alphaInc * (i + 1)) * radius << " "
             << 0 << " " << -1 << " " << 0 << " "
             << 0.5f + 0.5f * cos(alphaInc * (i + 1)) << " " << 0.5f + 0.5f * sin(alphaInc * (i + 1)) << endl;

        cone << 0 << " " << 0 << " " << 0 << " "
             << 0 << " " << -1 << " " << 0 << " "
             << 0.5f << " " << 0.5f << endl;
    }

    // Draw Sides
    for (int i = 0; i < stacks; i++)
    {
        currentHeight = heightInc * i;
        currentRadius = radius - (radiusDec * i);

        texX = 0.0f;
        texY = i * texYInc;

        for (int j = 0; j < slices; j++)
        {
            // Last stack: 1 slice - 1 triangle
            if (i == (stacks - 1))
            {
                normal[0] = cos(alphaInc * j);
                normal[1] = ny;
                normal[2] = sin(alphaInc * j);
                normalize(normal);

                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * (j * texXInc) << " " << texY << endl;

                normal[0] = cos(alphaInc * (j + 1));
                normal[1] = ny;
                normal[2] = sin(alphaInc * (j + 1));
                normalize(normal);

                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * ((j + 1) * texXInc) << " " << texY << endl;

                cone << cos(alphaInc * (j + 1)) * currentRadius << " " << currentHeight << " " << sin(alphaInc * (j + 1)) * currentRadius << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * ((j + 1) * texXInc) << " " << texY << endl;
            }
            else
            {
                normal[0] = cos(alphaInc * j);
                normal[1] = ny;
                normal[2] = sin(alphaInc * j);
                normalize(normal);

                // Bottom triangle
                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * (j * texXInc) << " " << texY << endl;

                normal[0] = cos(alphaInc * (j + 1));
                normal[1] = ny;
                normal[2] = sin(alphaInc * (j + 1));
                normalize(normal);

                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * ((j + 1) * texXInc) << " " << texY << endl;

                cone << cos(alphaInc * (j + 1)) * currentRadius << " " << currentHeight << " " << sin(alphaInc * (j + 1)) * currentRadius << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * ((j + 1) * texXInc) << " " << texY << endl;

                normal[0] = cos(alphaInc * j);
                normal[1] = ny;
                normal[2] = sin(alphaInc * j);
                normalize(normal);

                // Top triangle
                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * (j * texXInc) << " " << texY << endl;

                cone << cos(alphaInc * j) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * j) * (currentRadius - radiusDec) << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * (j * texXInc) << " " << texY << endl;

                normal[0] = cos(alphaInc * (j + 1));
                normal[1] = ny;
                normal[2] = sin(alphaInc * (j + 1));
                normalize(normal);

                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " "
                     << normal[0] << " " << normal[1] << " " << normal[2] << " "
                     << texX + 0.5f * ((j + 1) * texXInc) << " " << texY << endl;
            }
        }
    }
    cone.close();
    cout << filename << createFileSuccess << endl;
    return 0;
}

int createRing(float innerRadius, float outerRadius, int slices, char *filename)
{

    ofstream ring;
    ring.open(filename, std::ios::out | std::ios::trunc);

    if (!ring)
    {
        cout << openFileError << endl;
        return 1;
    }

    float alphaInc = 2 * M_PI / (float)slices;
    float p1x, p1z, p2x, p2z, p3x, p3z, p4x, p4z, texCenter;
    float t1x, t1y, t2x, t2y, t3x, t3y, t4x, t4y;
    texCenter = 0.5f;
    float texInnerRadius = 0.3f, texOutterRadius = 0.5f;

    float texInc = 1.0f / slices;

    for (int i = 0; i < slices; i++)
    {
        p1x = sin(alphaInc * i) * innerRadius;
        p1z = cos(alphaInc * i) * innerRadius;
        t1x = i * texInc;
        t1y = 0.0f;

        p2x = sin(alphaInc * i) * outerRadius;
        p2z = cos(alphaInc * i) * outerRadius;
        t2x = i * texInc;
        t2y = 1.0f;

        p3x = sin(alphaInc * (i + 1)) * innerRadius;
        p3z = cos(alphaInc * (i + 1)) * innerRadius;
        t3x = (i + 1) * texInc;
        t3y = 0.0f;

        p4x = sin(alphaInc * (i + 1)) * outerRadius;
        p4z = cos(alphaInc * (i + 1)) * outerRadius;
        t4x = (i + 1) * texInc;
        t4y = 1.0f;

        // Top view
        ring << p1x << " " << 0 << " " << p1z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t1x << " " << t1y << endl;
        ring << p2x << " " << 0 << " " << p2z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t2x << " " << t2y << endl;
        ring << p3x << " " << 0 << " " << p3z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t3x << " " << t3y << endl;

        ring << p2x << " " << 0 << " " << p2z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t2x << " " << t2y << endl;
        ring << p4x << " " << 0 << " " << p4z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t4x << " " << t4y << endl;
        ring << p3x << " " << 0 << " " << p3z << " "
             << 0 << " " << 1 << " " << 0 << " "
             << t3x << " " << t3y << endl;

        // Bottom view
        ring << p1x << " " << 0 << " " << p1z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t1x << " " << t1y << endl;
        ring << p3x << " " << 0 << " " << p3z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t3x << " " << t3y << endl;
        ring << p2x << " " << 0 << " " << p2z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t2x << " " << t2y << endl;

        ring << p2x << " " << 0 << " " << p2z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t2x << " " << t2y << endl;
        ring << p3x << " " << 0 << " " << p3z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t3x << " " << t3y << endl;
        ring << p4x << " " << 0 << " " << p4z << " "
             << 0 << " " << -1 << " " << 0 << " "
             << t4x << " " << t4y << endl;
    }

    ring.close();
    cout << filename << createFileSuccess << endl;
    return 0;
}

vector<vector<vector<float> > > loadPatch(char *filename)
{
    std::ifstream patchFile;

    int numberOfPatches = 0;
    int numberOfControlPoints = 0;
    string line;

    vector<vector<float> > controlPoints;
    vector<vector<int> > controlPointsIndices;
    vector<vector<vector<float> > > patchInfo;

    char delim = ' ';
    int start, end;
    string coord;

    patchFile.open(filename, std::ios::in);

    if (patchFile.is_open())
    {
        getline(patchFile, line);
        numberOfPatches = std::stoi(line);

        for (int i = 0; i < numberOfPatches; i++)
        {
            getline(patchFile, line);

            vector<int> indices;
            start = end = 0;

            while ((start = line.find_first_not_of(delim, end)) != string::npos)
            {
                end = line.find(delim, start);
                indices.push_back(std::stoi(line.substr(start, end - start)));
            }
            controlPointsIndices.push_back(indices);
        }

        getline(patchFile, line);
        numberOfControlPoints = std::stoi(line);

        while (getline(patchFile, line))
        {
            start = end = 0;
            vector<float> point;

            while ((start = line.find_first_not_of(delim, end)) != string::npos)
            {
                end = line.find(delim, start);
                point.push_back(std::stof(line.substr(start, end - start)));
            }
            controlPoints.push_back(point);
        }

        patchFile.close();
    }

    for (int i = 0; i < numberOfPatches; i++)
    {
        vector<vector<float> > patch;
        vector<int> indices = controlPointsIndices[i];
        for (int indice : indices)
        {
            patch.push_back(controlPoints[indice]);
        }
        patchInfo.push_back(patch);
    }

    return patchInfo;
}

int createPrimitive(vector<vector<vector<float> > > patchInfo, float tesselattion, char *destFilename)
{
    ofstream primitive;
    primitive.open(destFilename, std::ios::out | std::ios::trunc);

    if (!primitive)
    {
        cout << openFileError << endl;
        return 1;
    }

    float interval = 1.0f / tesselattion;
    float u, v;
    u = v = 0.0f;
    float pointA[3], pointB[3], pointC[3], pointD[3];
    float normalA[3], normalB[3], normalC[3], normalD[3];

    for (auto patch : patchInfo)
    {
        for (int i = 0; i < tesselattion; i++, u += interval)
        {
            for (int j = 0; j < tesselattion; j++, v += interval)
            {
                // Calculate points and normals to draw a triangle
                bezierSurfacePoint(u, v, patch, pointA, normalA);
                bezierSurfacePoint(u, v + interval, patch, pointB, normalB);
                bezierSurfacePoint(u + interval, v, patch, pointC, normalC);
                bezierSurfacePoint(u + interval, v + interval, patch, pointD, normalD);

                // Save triangle points and normals
                // 1st triangle
                primitive << pointA[0] << " " << pointA[1] << " " << pointA[2] << " "
                          << normalA[0] << " " << normalA[1] << " " << normalA[2] << " "
                          << (1 - v) << " " << (1 - u) << endl;
                primitive << pointB[0] << " " << pointB[1] << " " << pointB[2] << " "
                          << normalB[0] << " " << normalB[1] << " " << normalB[2] << " "
                          << (1 - (v + interval)) << " " << (1 - u) << endl;
                primitive << pointC[0] << " " << pointC[1] << " " << pointC[2] << " "
                          << normalC[0] << " " << normalC[1] << " " << normalC[2] << " "
                          << (1 - v) << " " << (1 - (u + interval)) << endl;

                // 2nd triangle
                primitive << pointD[0] << " " << pointD[1] << " " << pointD[2] << " "
                          << normalD[0] << " " << normalD[1] << " " << normalD[2] << " "
                          << (1 - (v + interval)) << " " << (1 - (u + interval)) << endl;
                primitive << pointC[0] << " " << pointC[1] << " " << pointC[2] << " "
                          << normalC[0] << " " << normalC[1] << " " << normalC[2] << " "
                          << (1 - v) << " " << (1 - (u + interval)) << endl;
                primitive << pointB[0] << " " << pointB[1] << " " << pointB[2] << " "
                          << normalB[0] << " " << normalB[1] << " " << normalB[2] << " "
                          << (1 - (v + interval)) << " " << (1 - u) << endl;
            }
            v = 0.0f;
        }
        u = v = 0.0f;
    }

    primitive.close();
    cout << destFilename << createFileSuccess << endl;
    return 0;
}

void multiplyMatrix(float *m1, int m1Rows, int m1Columns, float *m2, int m2Rows, int m2Columns, float *resM)
{
    if (m1Columns == m2Rows)
    {
        for (int i = 0; i < m1Rows; i++)
        {
            for (int j = 0; j < m2Columns; j++)
            {
                resM[i * m2Columns + j] = 0;
                for (int k = 0; k < m1Columns; k++)
                {
                    resM[i * m2Columns + j] += m1[i * m1Columns + k] * m2[k * m2Columns + j];
                }
            }
        }
    }
}

void bezierSurfacePoint(float u, float v, vector<vector<float> > patch, float *point, float *normal)
{
    float bezierM[16] = {-1.0f, 3.0f, -3.0f, 1.0f,
                         3.0f, -6.0f, 3.0f, 0.0f,
                         -3.0f, 3.0f, 0.0f, 0.0f,
                         1.0f, 0.0f, 0.0f, 0.0f};

    float uM[4] = {u * u * u, u * u, u, 1.0f};
    float vM[4] = {v * v * v, v * v, v, 1.0f};
    // d'(u)
    float duM[4] = {3.0f * u * u, 2.0f * u, 1.0f, 0.0f};
    // d'(v)
    float dvM[4] = {3.0f * v * v, 2.0f * v, 1.0f, 0.0f};

    float uMbezierM[4];
    multiplyMatrix(uM, 1, 4, bezierM, 4, 4, uMbezierM);

    float bezierMvM[4];
    multiplyMatrix(bezierM, 4, 4, vM, 4, 1, bezierMvM);

    // d'(u) x bezier
    float duMbezierM[4];
    multiplyMatrix(duM, 1, 4, bezierM, 4, 4, duMbezierM);

    // bezier x d'(v)
    float bezierMdvM[4];
    multiplyMatrix(bezierM, 4, 4, dvM, 4, 1, bezierMdvM);

    float P[3][16];
    for (int i = 0; i < 16; i++)
    {
        P[0][i] = patch[i][0];
        P[1][i] = patch[i][1];
        P[2][i] = patch[i][2];
    }

    for (int j = 0; j < 3; j++)
    {
        float uMbezierMP[4];
        multiplyMatrix(uMbezierM, 1, 4, P[j], 4, 4, uMbezierMP);
        multiplyMatrix(uMbezierMP, 1, 4, bezierMvM, 4, 1, &point[j]);
    }

    float dUPoint[3];
    float dVPoint[3];

    for (int i = 0; i < 3; i++)
    {
        float duMbezierMP[4];
        multiplyMatrix(duMbezierM, 1, 4, P[i], 4, 4, duMbezierMP);
        multiplyMatrix(duMbezierMP, 1, 4, bezierMvM, 4, 1, &dUPoint[i]);

        float uMbezierMP[4];
        multiplyMatrix(uMbezierM, 1, 4, P[i], 4, 4, uMbezierMP);
        multiplyMatrix(uMbezierMP, 1, 4, bezierMdvM, 4, 1, &dVPoint[i]);
    }

    cross(dVPoint, dUPoint, normal);
    normalize(normal);
}
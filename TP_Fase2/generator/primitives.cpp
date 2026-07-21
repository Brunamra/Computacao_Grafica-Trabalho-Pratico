#include "primitives.h"

std::string openFileError = "Something went wrong trying to open the file.";
std::string createFileSuccess = " created with success.";

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

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << endl;
                plane << (px + increment) << " " << py << " " << (pz + increment) << endl;
                plane << (px + increment) << " " << py << " " << pz << endl;

                plane << (px + increment) << " " << py << " " << (pz + increment) << endl;
                plane << px << " " << py << " " << pz << endl;
                plane << px << " " << py << " " << (pz + increment) << endl;
            }
            else
            {
                plane << px << " " << -py << " " << pz << endl;
                plane << (px + increment) << " " << -py << " " << pz << endl;
                plane << (px + increment) << " " << -py << " " << (pz + increment) << endl;

                plane << (px + increment) << " " << -py << " " << (pz + increment) << endl;
                plane << px << " " << -py << " " << (pz + increment) << endl;
                plane << px << " " << -py << " " << pz << endl;
            }
            px += increment;
        }
        px = -mid;
        pz += increment;
    }
    plane.close();
    !front &&cout << filename << createFileSuccess << endl;
    ;
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

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << endl;
                plane << (px + increment) << " " << py << " " << pz << endl;
                plane << (px + increment) << " " << (py + increment) << " " << pz << endl;

                plane << (px + increment) << " " << (py + increment) << " " << pz << endl;
                plane << px << " " << (py + increment) << " " << pz << endl;
                plane << px << " " << py << " " << pz << endl;
            }
            else
            {
                plane << px << " " << py << " " << -pz << endl;
                plane << (px + increment) << " " << (py + increment) << " " << -pz << endl;
                plane << (px + increment) << " " << py << " " << -pz << endl;

                plane << (px + increment) << " " << (py + increment) << " " << -pz << endl;
                plane << px << " " << py << " " << -pz << endl;
                plane << px << " " << (py + increment) << " " << -pz << endl;
            }
            px += increment;
        }
        px = -mid;
        py += increment;
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

    // plane << nv << endl;
    for (int i = 0; i < divisions; i++)
    {
        for (int j = 0; j < divisions; j++)
        {
            if (front >= 0)
            {
                plane << px << " " << py << " " << pz << endl;
                plane << px << " " << (py + increment) << " " << (pz + increment) << endl;
                plane << px << " " << py << " " << (pz + increment) << endl;

                plane << px << " " << (py + increment) << " " << (pz + increment) << endl;
                plane << px << " " << py << " " << pz << endl;
                plane << px << " " << (py + increment) << " " << pz << endl;
            }
            else
            {
                plane << -px << " " << py << " " << pz << endl;
                plane << -px << " " << py << " " << (pz + increment) << endl;
                plane << -px << " " << (py + increment) << " " << (pz + increment) << endl;

                plane << -px << " " << (py + increment) << " " << (pz + increment) << endl;
                plane << -px << " " << (py + increment) << " " << pz << endl;
                plane << -px << " " << py << " " << pz << endl;
            }
            pz += increment;
        }
        pz = -mid;
        py += increment;
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

    for (int i = 0; i < stacks; i++)
    {
        beta = -(M_PI / 2.0f) + i * betaInc;

        for (int j = 0; j < slices; j++)
        {
            alpha = j * alphaInc;
            if (i == 0)
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << endl;
                // top left
                sphere << radius * cos(beta + betaInc) * sin(alpha) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha)
                       << endl;
            }
            else if (i == stacks - 1)
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << endl;
                // bottom right
                sphere << radius * cos(beta) * sin(alpha + alphaInc) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha + alphaInc)
                       << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << endl;
            }
            else
            {
                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << endl;
                // bottom right
                sphere << radius * cos(beta) * sin(alpha + alphaInc) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha + alphaInc)
                       << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << endl;

                // bottom left
                sphere << radius * cos(beta) * sin(alpha) << " " << radius * sin(beta) << " " << radius * cos(beta) * cos(alpha)
                       << endl;
                // top right
                sphere << radius * cos(beta + betaInc) * sin(alpha + alphaInc) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha + alphaInc)
                       << endl;
                // top left
                sphere << radius * cos(beta + betaInc) * sin(alpha) << " " << radius * sin(beta + betaInc) << " " << radius * cos(beta + betaInc) * cos(alpha)
                       << endl;
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

    // Draw Base
    for (int i = 0; i < slices; i++)
    {
        cone << cos(alphaInc * i) * radius << " " << 0 << " " << sin(alphaInc * i) * radius << endl;
        cone << cos(alphaInc * (i + 1)) * radius << " " << 0 << " " << sin(alphaInc * (i + 1)) * radius << endl;
        cone << 0 << " " << 0 << " " << 0 << endl;
    }

    // Draw Sides
    for (int i = 0; i < stacks; i++)
    {
        currentHeight = heightInc * i;
        currentRadius = radius - (radiusDec * i);

        for (int j = 0; j < slices; j++)
        {
            // Last stack: 1 slice - 1 triangle
            if (i == (stacks - 1))
            {
                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << endl;
                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << endl;
                cone << cos(alphaInc * (j + 1)) * currentRadius << " " << currentHeight << " " << sin(alphaInc * (j + 1)) * currentRadius << endl;
            }
            else
            {
                // Bottom triangle
                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << endl;
                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << endl;
                cone << cos(alphaInc * (j + 1)) * currentRadius << " " << currentHeight << " " << sin(alphaInc * (j + 1)) * currentRadius << endl;

                // Top triangle
                cone << cos(alphaInc * j) * currentRadius << " " << currentHeight << " " << sin(alphaInc * j) * currentRadius << endl;
                cone << cos(alphaInc * j) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * j) * (currentRadius - radiusDec) << endl;
                cone << cos(alphaInc * (j + 1)) * (currentRadius - radiusDec) << " " << currentHeight + heightInc << " " << sin(alphaInc * (j + 1)) * (currentRadius - radiusDec) << endl;
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
    float p1x, p1z, p2x, p2z, p3x, p3z, p4x, p4z;

    for (int i = 0; i < slices; i++)
    {
        p1x = sin(alphaInc * i) * innerRadius;
        p1z = cos(alphaInc * i) * innerRadius;
        p2x = sin(alphaInc * i) * outerRadius;
        p2z = cos(alphaInc * i) * outerRadius;
        p3x = sin(alphaInc * (i + 1)) * innerRadius;
        p3z = cos(alphaInc * (i + 1)) * innerRadius;
        p4x = sin(alphaInc * (i + 1)) * outerRadius;
        p4z = cos(alphaInc * (i + 1)) * outerRadius;

        // Top view
        ring << p1x << " " << 0 << " " << p1z << endl;
        ring << p2x << " " << 0 << " " << p2z << endl;
        ring << p3x << " " << 0 << " " << p3z << endl;

        ring << p2x << " " << 0 << " " << p2z << endl;
        ring << p4x << " " << 0 << " " << p4z << endl;
        ring << p3x << " " << 0 << " " << p3z << endl;

        // Bottom view
        ring << p1x << " " << 0 << " " << p1z << endl;
        ring << p3x << " " << 0 << " " << p3z << endl;
        ring << p2x << " " << 0 << " " << p2z << endl;

        ring << p2x << " " << 0 << " " << p2z << endl;
        ring << p3x << " " << 0 << " " << p3z << endl;
        ring << p4x << " " << 0 << " " << p4z << endl;
    }

    ring.close();
    cout << filename << createFileSuccess << endl;
    return 0;
}
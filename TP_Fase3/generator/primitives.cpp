#include "primitives.h"

string openFileError = "Something went wrong trying to open the file.";
string createFileSuccess = " created with success.";

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

vector<vector<vector<float>>> loadPatch(char *filename)
{
    std::ifstream patchFile;

    int numberOfPatches = 0;
    int numberOfControlPoints = 0;
    string line;

    vector<vector<float>> controlPoints;
    vector<vector<int>> controlPointsIndices;
    vector<vector<vector<float>>> patchInfo;

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
        vector<vector<float>> patch;
        vector<int> indices = controlPointsIndices[i];
        for (int indice : indices)
        {
            patch.push_back(controlPoints[indice]);
        }
        patchInfo.push_back(patch);
    }

    return patchInfo;
}

int createPrimitive(vector<vector<vector<float>>> patchInfo, float tesselattion, char *destFilename)
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

    for (auto patch : patchInfo)
    {
        for (int i = 0; i < tesselattion; i++, u += interval)
        {
            for (int j = 0; j < tesselattion; j++, v += interval)
            {
                // Calculate points to draw a triangle
                bezierSurfacePoint(u, v, patch, pointA);
                bezierSurfacePoint(u, v + interval, patch, pointB);
                bezierSurfacePoint(u + interval, v, patch, pointC);
                bezierSurfacePoint(u + interval, v + interval, patch, pointD);

                // Save triangle points
                // 1st triangle
                primitive << pointC[0] << " " << pointC[1] << " " << pointC[2] << endl;
                primitive << pointA[0] << " " << pointA[1] << " " << pointA[2] << endl;
                primitive << pointB[0] << " " << pointB[1] << " " << pointB[2] << endl;

                // 2nd triangle
                primitive << pointB[0] << " " << pointB[1] << " " << pointB[2] << endl;
                primitive << pointD[0] << " " << pointD[1] << " " << pointD[2] << endl;
                primitive << pointC[0] << " " << pointC[1] << " " << pointC[2] << endl;
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

void bezierSurfacePoint(float u, float v, vector<vector<float>> patch, float *point)
{
    float bezierM[16] = {-1.0f, 3.0f, -3.0f, 1.0f,
                         3.0f, -6.0f, 3.0f, 0.0f,
                         -3.0f, 3.0f, 0.0f, 0.0f,
                         1.0f, 0.0f, 0.0f, 0.0f};

    float uM[4] = {u * u * u, u * u, u, 1.0f};
    float vM[4] = {v * v * v, v * v, v, 1.0f};

    float uMbezierM[4];
    float bezierMvM[4];

    multiplyMatrix(uM, 1, 4, bezierM, 4, 4, uMbezierM);
    multiplyMatrix(bezierM, 4, 4, vM, 4, 1, bezierMvM);

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
}

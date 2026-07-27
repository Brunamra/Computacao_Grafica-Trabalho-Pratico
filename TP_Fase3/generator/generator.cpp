#include "primitives.h"

using std::cout;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Not enough arguments." << endl;
        return -1;
    }

    if (strcmp(argv[1], "plane") == 0)
    {
        if (argc == 5)
        {
            createPlaneXZ(atoi(argv[2]), atoi(argv[3]), argv[4]);
            return 1;
        }
        if (argc == 6)
        {
            createPlaneXZ(atoi(argv[2]), atoi(argv[3]), argv[4], atoi(argv[5]));
            return 1;
        }
        else
        {
            cout << "Use: ./generator plane <lenght> <divisions> <filename>" << endl;
            return -1;
        }
    }
    if (strcmp(argv[1], "box") == 0)
    {
        if (argc == 5)
        {
            createBox(atoi(argv[2]), atoi(argv[3]), argv[4]);
            return 1;
        }
        else
        {
            cout << "Use: ./generator box <lenght> <divisions> <filename>" << endl;
            return -1;
        }
    }
    if (strcmp(argv[1], "sphere") == 0)
    {
        if (argc == 6)
        {
            createSphere(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5]);
        }
        else
        {
            cout << "Use: ./generator sphere <radius> <slices> <stacks> <filename>" << endl;
            return -1;
        }
    }
    if (strcmp(argv[1], "cone") == 0)
    {
        if (argc == 7)
        {
            createCone(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
        }
        else
        {
            cout << "Use: ./generator cone <radius> <height> <slices> <stacks> <filename>" << endl;
            return -1;
        }
    }
    if (strcmp(argv[1], "ring") == 0)
    {
        if (argc == 6)
        {
            createRing(atof(argv[2]), atof(argv[3]), atoi(argv[4]), argv[5]);
        }
        else
        {
            cout << "Use: ./generator ring <innerRadius> <outerRadius> <slices> <filename>" << endl;
            return -1;
        }
    }
    if (strcmp(argv[1], "patch") == 0)
    {
        if (argc == 5)
        {
            vector<vector<vector<float>>> patchInfo = loadPatch(argv[2]);
            createPrimitive(patchInfo, atoi(argv[3]), argv[4]);
        }
        else
        {
            cout << "Use: ./generator patch <source filename> <tessellation> <destiny filename>" << endl;
            return -1;
        }
    }

    return 0;
}
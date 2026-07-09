#include "config.h"

int xmlToConfig(Config *conf, string xmlFile)
{
    if (conf == NULL)
    {
        return 1;
    }

    XMLDocument xmlDoc;
    XMLError result = xmlDoc.LoadFile(xmlFile.c_str());
    if (result != XML_SUCCESS)
    {
        cout << "Error trying to load file" << endl;
        return result;
    }

    XMLElement *pWorld = xmlDoc.FirstChildElement("world");

    XMLElement *pWindow = pWorld->FirstChildElement("window");
    addToWindow(conf, atoi(pWindow->Attribute("width")), atoi(pWindow->Attribute("height")));

    XMLElement *pCamera = pWorld->FirstChildElement("camera");
    XMLElement *pPosition = pCamera->FirstChildElement("position");
    addToPosition(conf, atof(pPosition->Attribute("x")), atof(pPosition->Attribute("y")), atof(pPosition->Attribute("z")));

    XMLElement *pLookAt = pCamera->FirstChildElement("lookAt");
    addToLookAt(conf, atof(pLookAt->Attribute("x")), atof(pLookAt->Attribute("y")), atof(pLookAt->Attribute("z")));

    XMLElement *pUp = pCamera->FirstChildElement("up");
    addToUp(conf, atof(pUp->Attribute("x")), atof(pUp->Attribute("y")), atof(pUp->Attribute("z")));

    XMLElement *pProjection = pCamera->FirstChildElement("projection");
    addToProjection(conf, atof(pProjection->Attribute("fov")), atof(pProjection->Attribute("near")), atof(pProjection->Attribute("far")));

    XMLElement *pGroup = pWorld->FirstChildElement("group");
    XMLElement *pModels = pGroup->FirstChildElement("models");
    XMLElement *pModel = pModels->FirstChildElement("model");

    while (pModel != nullptr)
    {
        addToModels(conf, pModel->Attribute("file"));
        pModel = pModel->NextSiblingElement("model");
    }

    return XML_SUCCESS;
}

int addToWindow(Config *conf, int width, int height)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->window[0] = width;
    conf->window[1] = height;
    return 0;
}

int addToPosition(Config *conf, float x, float y, float z)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->position[0] = x;
    conf->position[1] = y;
    conf->position[2] = z;
    return 0;
}

int addToLookAt(Config *conf, float x, float y, float z)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->lookAt[0] = x;
    conf->lookAt[1] = y;
    conf->lookAt[2] = z;
    return 0;
}

int addToUp(Config *conf, float x, float y, float z)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->up[0] = x;
    conf->up[1] = y;
    conf->up[2] = z;
    return 0;
}

int addToProjection(Config *conf, float fov, float near, float far)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->projection[0] = fov;
    conf->projection[1] = near;
    conf->projection[2] = far;
    return 0;
}

int addToModels(Config *conf, string model)
{
    if (conf == NULL)
    {
        return 1;
    }
    conf->models.insert(pair<string, vector<Point>>(model, vector<Point>()));
    return 0;
}

int loadModelVertex(Config *conf, string model)
{
    std::ifstream primitive;
    float px, py, pz;
    Point p;

    primitive.open(model, std::ios::in);

    if (primitive.is_open())
    {
        while (primitive >> px >> py >> pz)
        {
            p.px = px;
            p.py = py;
            p.pz = pz;
            conf->models[model].push_back(p);
        }
        primitive.close();
        return 0;
    }

    cout << "Something went wrong trying to open the file." << endl;

    return 1;
}
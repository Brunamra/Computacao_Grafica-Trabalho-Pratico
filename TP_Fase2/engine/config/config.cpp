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
    // Add groups recursively
    conf->group = addGroup(pGroup, conf);

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

Group addGroup(XMLElement *group_pointer, Config *conf)
{
    Group group;

    // ADD TRANSFORMS
    XMLElement *pTransform = group_pointer->FirstChildElement("transform");
    if (pTransform != nullptr)
    {
        XMLElement *pCurrentTransform = pTransform->FirstChildElement();

        while (pCurrentTransform != nullptr)
        {
            Point p;
            p.px = atof(pCurrentTransform->Attribute("x"));
            p.py = atof(pCurrentTransform->Attribute("y"));
            p.pz = atof(pCurrentTransform->Attribute("z"));

            Transform trans;
            trans.coords = p;
            trans.angle = 0.0;

            if (strcmp(pCurrentTransform->Value(), "translate") == 0)
            {
                // add to transformation type 0
                trans.type = 0;
                group.transforms.push_back(trans);
            }
            else if (strcmp(pCurrentTransform->Value(), "rotate") == 0)
            {
                // add to transformation type 1
                float angle = atof(pCurrentTransform->Attribute("angle"));
                trans.type = 1;
                trans.angle = angle;

                group.transforms.push_back(trans);
            }
            else if (strcmp(pCurrentTransform->Value(), "scale") == 0)
            {
                // add to transformation type 2
                trans.type = 2;
                group.transforms.push_back(trans);
            }
            pCurrentTransform = pCurrentTransform->NextSiblingElement();
        }
    }

    XMLElement *pModels = group_pointer->FirstChildElement("models");
    if (pModels != nullptr)
    {
        XMLElement *pModel = pModels->FirstChildElement("model");

        while (pModel != nullptr)
        {
            addToModels(conf, pModel->Attribute("file"));
            group.models.push_back(pModel->Attribute("file"));
            pModel = pModel->NextSiblingElement("model");
        }
    }

    XMLElement *pChildGroup = group_pointer->FirstChildElement("group");
    while (pChildGroup != nullptr)
    {
        group.groups.push_back(addGroup(pChildGroup, conf));
        pChildGroup = pChildGroup->NextSiblingElement("group");
    }

    return group;
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

void printGroup(Group group)
{
    if (!group.transforms.empty())
    {
        for (vector<Transform>::iterator it = group.transforms.begin(); it != group.transforms.end(); it++)
        {
            cout << "TYPE: " << it->type << endl
                 << "COORDS X: " << it->coords.px << endl
                 << "COORDS Y: " << it->coords.py << endl
                 << "COORDS Z: " << it->coords.pz << endl
                 << "ANGLE: " << it->angle << endl;
            ;
        }
    }
    if (!group.models.empty())
    {
        for (vector<string>::iterator it = group.models.begin(); it != group.models.end(); it++)
        {
            cout << *it << endl;
            ;
        }
    }
    if (!group.groups.empty())
    {
        for (vector<Group>::iterator it = group.groups.begin(); it != group.groups.end(); it++)
        {
            printGroup(*it);
        }
    }
}
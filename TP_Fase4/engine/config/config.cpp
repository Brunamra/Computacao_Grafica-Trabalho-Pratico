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

    XMLElement *pLights = pWorld->FirstChildElement("lights");
    if (pLights != nullptr)
    {
        XMLElement *pLight = pLights->FirstChildElement("light");
        while (pLight != nullptr)
        {
            Light light;
            if (strcmp(pLight->Attribute("type"), "point") == 0)
            {
                light.type = 0;
                light.pos[0] = atof(pLight->Attribute("posx"));
                light.pos[1] = atof(pLight->Attribute("posy"));
                light.pos[2] = atof(pLight->Attribute("posz"));
            }
            else if (strcmp(pLight->Attribute("type"), "directional") == 0)
            {
                light.type = 1;
                light.dir[0] = atof(pLight->Attribute("dirx"));
                light.dir[1] = atof(pLight->Attribute("diry"));
                light.dir[2] = atof(pLight->Attribute("dirz"));
            }
            else if (strcmp(pLight->Attribute("type"), "spot") == 0)
            {
                light.type = 2;
                light.pos[0] = atof(pLight->Attribute("posx"));
                light.pos[1] = atof(pLight->Attribute("posy"));
                light.pos[2] = atof(pLight->Attribute("posz"));
                light.dir[0] = atof(pLight->Attribute("dirx"));
                light.dir[1] = atof(pLight->Attribute("diry"));
                light.dir[2] = atof(pLight->Attribute("dirz"));
                light.cuttOff = atof(pLight->Attribute("cutoff"));
            }

            conf->lights.push_back(light);

            pLight = pLight->NextSiblingElement("light");
        }
    }

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
    conf->models.insert(pair<string, ModelInfo>(model, ModelInfo()));
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
            p.px = (pCurrentTransform->Attribute("x") != nullptr) ? atof(pCurrentTransform->Attribute("x")) : 0.0;
            p.py = (pCurrentTransform->Attribute("y") != nullptr) ? atof(pCurrentTransform->Attribute("y")) : 0.0;
            p.pz = (pCurrentTransform->Attribute("z") != nullptr) ? atof(pCurrentTransform->Attribute("z")) : 0.0;

            Transform trans;
            trans.coords = p;
            trans.angle = 0.0;

            if (strcmp(pCurrentTransform->Value(), "translate") == 0)
            {
                // add to transformation type 0
                trans.type = 0;
                if (pCurrentTransform->Attribute("time") != nullptr)
                {
                    trans.time = atof(pCurrentTransform->Attribute("time"));
                }
                if (pCurrentTransform->Attribute("align") != nullptr)
                {
                    if (strcmp(pCurrentTransform->Attribute("align"), "true") == 0)
                    {
                        trans.align = 1;
                    }
                    else
                    {
                        trans.align = 0;
                    }
                }
                XMLElement *pTranslatePoints = pCurrentTransform->FirstChildElement("point");
                while (pTranslatePoints != nullptr)
                {
                    Point transPoint;
                    transPoint.px = atof(pTranslatePoints->Attribute("x"));
                    transPoint.py = atof(pTranslatePoints->Attribute("y"));
                    transPoint.pz = atof(pTranslatePoints->Attribute("z"));

                    trans.points.push_back(transPoint);

                    pTranslatePoints = pTranslatePoints->NextSiblingElement("point");
                }
                group.transforms.push_back(trans);
            }
            else if (strcmp(pCurrentTransform->Value(), "rotate") == 0)
            {
                // add to transformation type 1
                float angle = pCurrentTransform->Attribute("angle") ? atof(pCurrentTransform->Attribute("angle")) : 0.0;
                trans.type = 1;
                trans.angle = angle;

                if (pCurrentTransform->Attribute("time") != nullptr)
                {
                    trans.time = atof(pCurrentTransform->Attribute("time"));
                }

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
            ModelSettings modelSet;
            modelSet.modelFile = pModel->Attribute("file");

            XMLElement *pModelSettings = pModel->FirstChildElement("texture");
            if (pModelSettings != nullptr)
            {
                modelSet.textureFile = pModelSettings->Attribute("file");
            }

            Color color;
            XMLElement *pModelColor = pModel->FirstChildElement("color");

            if (pModelColor != nullptr)
            {
                XMLElement *pAmbient = pModelColor->FirstChildElement("ambient");
                if (pAmbient != nullptr)
                {
                    color.ambient[0] = (atof(pAmbient->Attribute("R")) / 255.0f);
                    color.ambient[1] = (atof(pAmbient->Attribute("G")) / 255.0f);
                    color.ambient[2] = (atof(pAmbient->Attribute("B")) / 255.0f);
                }

                XMLElement *pDiffuse = pModelColor->FirstChildElement("diffuse");
                if (pDiffuse != nullptr)
                {
                    color.diffuse[0] = (atof(pDiffuse->Attribute("R")) / 255.0f);
                    color.diffuse[1] = (atof(pDiffuse->Attribute("G")) / 255.0f);
                    color.diffuse[2] = (atof(pDiffuse->Attribute("B")) / 255.0f);
                }

                XMLElement *pSpecular = pModelColor->FirstChildElement("specular");
                if (pSpecular != nullptr)
                {
                    color.specular[0] = (atof(pSpecular->Attribute("R")) / 255.0f);
                    color.specular[1] = (atof(pSpecular->Attribute("G")) / 255.0f);
                    color.specular[2] = (atof(pSpecular->Attribute("B")) / 255.0f);
                }

                XMLElement *pEmissisve = pModelColor->FirstChildElement("emissive");
                if (pEmissisve != nullptr)
                {
                    color.emissive[0] = (atof(pEmissisve->Attribute("R")) / 255.0f);
                    color.emissive[1] = (atof(pEmissisve->Attribute("G")) / 255.0f);
                    color.emissive[2] = (atof(pEmissisve->Attribute("B")) / 255.0f);
                }

                XMLElement *pShininess = pModelColor->FirstChildElement("shininess");
                if (pShininess != nullptr)
                {
                    color.shininess = atof(pShininess->Attribute("value"));
                }
            }

            modelSet.color = color;

            addToModels(conf, pModel->Attribute("file"));
            group.models.push_back(modelSet);
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
    float px, py, pz, nx, ny, nz, texX, texY;
    Point p;
    Point n;
    TexCoord tex;

    primitive.open(model, std::ios::in);

    if (primitive.is_open())
    {
        while (primitive >> px >> py >> pz >> nx >> ny >> nz >> texX >> texY)
        {
            p.px = px;
            p.py = py;
            p.pz = pz;
            conf->models[model].vertices.push_back(p);
            n.px = nx;
            n.py = ny;
            n.pz = nz;
            conf->models[model].normals.push_back(n);
            tex.x = texX;
            tex.y = texY;
            conf->models[model].texCoords.push_back(tex);
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
            if (!it->points.empty())
            {
                cout << "TYPE: " << it->type << endl;
                cout << "TIME: " << it->time << endl;
                for (vector<Point>::iterator pt = it->points.begin(); pt != it->points.end(); pt++)
                {
                    cout << "POINT X: " << pt->px << endl;
                    cout << "POINT Y: " << pt->py << endl;
                    cout << "POINT Z: " << pt->pz << endl;
                }
            }
            else
            {
                cout << "TYPE: " << it->type << endl
                     << "TIME: " << it->time << endl
                     << "ANGLE: " << it->angle << endl
                     << "COORDS X: " << it->coords.px << endl
                     << "COORDS Y: " << it->coords.py << endl
                     << "COORDS Z: " << it->coords.pz << endl;
                ;
            }
        }
    }
    if (!group.models.empty())
    {
        for (vector<ModelSettings>::iterator it = group.models.begin(); it != group.models.end(); it++)
        {
            cout << it->modelFile << endl;
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

// Count number of models to create buffers
int modelsCount(Group group, int *result)
{
    if (!group.models.empty())
    {
        for (vector<ModelSettings>::iterator it = group.models.begin(); it != group.models.end(); it++)
        {
            (*result) += 1;
        }
    }
    if (!group.groups.empty())
    {
        for (vector<Group>::iterator it = group.groups.begin(); it != group.groups.end(); it++)
        {
            *result = modelsCount(*it, result);
        }
    }
    // cout << "Result: " << *result << endl;
    return *result;
};

vector<vector<float> > pointsToFloats(vector<Point> controlPoints)
{
    vector<vector<float> > controlPointsFloats;
    for (vector<Point>::iterator it = controlPoints.begin(); it != controlPoints.end(); it++)
    {
        vector<float> coords;
        coords.push_back(it->px);
        coords.push_back(it->py);
        coords.push_back(it->pz);
        controlPointsFloats.push_back(coords);
    }
    return controlPointsFloats;
}
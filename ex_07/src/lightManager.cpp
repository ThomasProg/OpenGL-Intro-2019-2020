#include "lightManager.h"
#include "macros.h"
#include "transform.h"

void LightManager::init()
{
    //Lightning
    glEnable(GL_LIGHTING);

    //set light0
    //glEnable(GL_LIGHT0);
    float ambient[4] = {0.2,0.2,0.2,1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    //float attenuation[4] = {0.5,0.5,0.5,0.5};
    float attenuation = 0.3;
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &attenuation);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    //materials
    glEnable(GL_COLOR_MATERIAL);

    GLfloat specular[4] = {0.9,0.9,0.9,1};
    GLfloat shininess = 64;
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

void LightManager::tick()
{
    glDisable(GL_LIGHT0);
    float defaultCutoff = 180;
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &defaultCutoff);
}

void LightManager::displayDirectionalLight()
{
    glEnable(GL_LIGHT0);
    float loc[4] = {5,5,5,0};
    glLightfv(GL_LIGHT0, GL_POSITION, loc);
}

void LightManager::displayPointLight()
{
    glEnable(GL_LIGHT0);
    float loc[4] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, loc);
}

void LightManager::displaySpotLight(Vector3 rotation)
{
    glEnable(GL_LIGHT0);
    float loc[4] = {0,0,0,1};
    glLightfv(GL_LIGHT0, GL_POSITION, loc);
    float defaultCutoff = 30;
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &defaultCutoff);
    float rot[3] = {0, 
                   static_cast<float>(sin(rotation.y/180*PI)  - cos(rotation.z/180*PI)), 
                   static_cast<float>(sin(rotation.y/180*PI) - cos(rotation.z/180*PI))};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, rot);
}

void LightManager::displayProofOfSpecularLight()
{
    glEnable(GL_LIGHT0);
    float loc[4] = {3,3,3,1};
    glLightfv(GL_LIGHT0, GL_POSITION, loc);
}
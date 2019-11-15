#ifndef _LIGHT_MANAGER_H_
#define _LIGHT_MANAGER_H_

//class GLFWwindow;
class Vector3;

class LightManager
{
private:

public:
    LightManager() {}
    ~LightManager() {}

    void init();
    void tick();

    void displayDirectionalLight();

    void displayPointLight();

    void displaySpotLight(Vector3 rotation);

    void displayProofOfSpecularLight();

};

#endif
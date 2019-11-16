#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "macros.h"
#include "transform.h"

constexpr float CAMERA_ROT_SPEED = 50.f;

class Camera
{
public:
    S_Transform transform;
    vec2 mouseLoc;
    double deltaTime;

    Camera() 
    {
        transform.rotation.x = 0.f;
    }

    void inputs(GLFWwindow* window)
    {
        vec2 newMouseLoc;
        glfwGetCursorPos(window, &newMouseLoc.x, &newMouseLoc.y);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GL_TRUE);

        mouseLoc = newMouseLoc;
    }

    void useTransform()
    {
		glTranslatef(-transform.location.x, 
                     -transform.location.y, 
                     -transform.location.z);

		glRotatef(transform.rotation.x, 1, 0, 0);
		glRotatef(transform.rotation.y, 0, 1, 0);
    }

    void reset()
    {
        transform.location = vector3D(0.f, 0.f, 0.f);
        transform.rotation = vector3D(0.f, 0.f, 0.f);
        transform.scale = vector3D(0.f, 0.f, 0.f);
    }
};

#endif
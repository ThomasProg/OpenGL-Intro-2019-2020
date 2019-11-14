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
        transform.rotation.x += 20.f;
    }

    // void down(float value)
    // {
    //     transform.location.x += value * sin(-transform.rotation.y/180*PI) * deltaTime;
    //     transform.location.z += value * cos(-transform.rotation.y/180*PI) * deltaTime;
    // }

    void inputs(GLFWwindow* window)
    {
        vec2 newMouseLoc;
        glfwGetCursorPos(window, &newMouseLoc.x, &newMouseLoc.y);

        //faster on diagonales : to fix
        // if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W))
        // {
        //     transform.location.x -= speed * sin(-transform.rotation.y/180*PI) * deltaTime;
        //     transform.location.z -= speed * cos(-transform.rotation.y/180*PI) * deltaTime;
        // }
        // if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S))
        // {
        //     transform.location.x += speed * sin(-transform.rotation.y/180*PI) * deltaTime;
        //     transform.location.z += speed * cos(-transform.rotation.y/180*PI) * deltaTime;
        // }
        // if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
        // {
        //     transform.location.x += speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        //     transform.location.z += speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        // }
        // if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
        // {
        //     transform.location.x -= speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        //     transform.location.z -= speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        // }

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

		//glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    }
};

#endif
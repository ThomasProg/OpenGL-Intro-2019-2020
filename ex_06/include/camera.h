#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "macros.h"
#include "transform.h"

class Camera
{
public:
    Camera() {}

    S_Transform transform;
    float speed = 0.1f, rotSpeed = 5.f;
    vec2 mouseLoc;
    float sensibility = 0.2;

    // void useTransform()
    // {
	// 	glRotatef(transform.rotation.x, 1, 0, 0);
	// 	glRotatef(transform.rotation.y, 0, 1, 0);
	// 	glRotatef(transform.rotation.z, 0, 0, 1);
	// 	glTranslatef(transform.location.x, transform.location.y, transform.location.z);
	// 	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    // }

    void inputs(GLFWwindow* window)
    {
        vec2 newMouseLoc;
        glfwGetCursorPos(window, &newMouseLoc.x, &newMouseLoc.y);

        //faster on diagonales : to fix
        if (glfwGetKey(window, GLFW_KEY_UP))
            transform.location.z += speed;
        if (glfwGetKey(window, GLFW_KEY_DOWN))
            transform.location.z -= speed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
            transform.location.x -= speed;
        if (glfwGetKey(window, GLFW_KEY_LEFT))
            transform.location.x += speed;

        transform.rotation.y -= (newMouseLoc.x - mouseLoc.x) * sensibility;//rotSpeed;
        transform.rotation.x -= (newMouseLoc.y - mouseLoc.y) * sensibility;//rotSpeed;   

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GL_TRUE);

        mouseLoc = newMouseLoc;
    }
};

#endif
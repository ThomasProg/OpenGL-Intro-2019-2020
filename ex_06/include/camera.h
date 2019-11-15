#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "macros.h"
#include "transform.h"

class Camera
{
public:
    S_Transform transform;
    float speed = 5.f;
    vec2 mouseLoc;
    float sensibility = 5.f;
    double deltaTime;

    static constexpr float hitboxSize = 2.f; 

    Vector3 lastLocation = Vector3(0, 0, 0);

    Camera() 
    {
        transform.location = transform.location 
            + Vector3((CHUNK_SIZE + BLOCK_SIZE) / 2, 
                      (CHUNK_SIZE + BLOCK_SIZE) / 2, 
                      (CHUNK_SIZE + BLOCK_SIZE) / 2);
    }

    void inputs(GLFWwindow* window)
    {
        vec2 newMouseLoc;
        glfwGetCursorPos(window, &newMouseLoc.x, &newMouseLoc.y);

        //faster on diagonales : to fix
        if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W))
        {
            transform.location.x -= speed * sin(-transform.rotation.y/180*PI) * deltaTime;
            transform.location.z -= speed * cos(-transform.rotation.y/180*PI) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S))
        {
            transform.location.x += speed * sin(-transform.rotation.y/180*PI) * deltaTime;
            transform.location.z += speed * cos(-transform.rotation.y/180*PI) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
        {
            transform.location.x += speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
            transform.location.z += speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
        {
            transform.location.x -= speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
            transform.location.z -= speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
        }

        transform.rotation.y += (newMouseLoc.x - mouseLoc.x) * sensibility * deltaTime;
        transform.rotation.x += (newMouseLoc.y - mouseLoc.y) * sensibility * deltaTime;   

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
            transform.location.y -= speed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_SPACE))
            transform.location.y += speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, GL_TRUE);

        mouseLoc = newMouseLoc;
    }

    void useTransform()
    {
		glRotatef(transform.rotation.x, 1, 0, 0);
		glRotatef(transform.rotation.y, 0, 1, 0);
		glTranslatef(-transform.location.x, 
                     -transform.location.y, 
                     -transform.location.z);

		glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    }
};

#endif
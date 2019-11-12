#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL2/SDL.h>
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

    void inputs(SDL_Event& event)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        vec2 newMouseLoc(x, y);

        if (event.type == SDL_KEYDOWN)
        {
            //faster on diagonales : to fix
            if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
            {
                transform.location.x -= speed * sin(-transform.rotation.y/180*PI) * deltaTime;
                transform.location.z -= speed * cos(-transform.rotation.y/180*PI) * deltaTime;
            }
            if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
            {
                transform.location.x += speed * sin(-transform.rotation.y/180*PI) * deltaTime;
                transform.location.z += speed * cos(-transform.rotation.y/180*PI) * deltaTime;
            }
            if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
            {
                transform.location.x += speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
                transform.location.z += speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
            }
            if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
            {
                transform.location.x -= speed * sin(-transform.rotation.y/180*PI + PI/2) * deltaTime;
                transform.location.z -= speed * cos(-transform.rotation.y/180*PI + PI/2) * deltaTime;
            }

            transform.rotation.y += (newMouseLoc.x - mouseLoc.x) * sensibility * deltaTime;//rotSpeed;
            transform.rotation.x += (newMouseLoc.y - mouseLoc.y) * sensibility * deltaTime;//rotSpeed;   

            if (event.key.keysym.sym == SDLK_LSHIFT)
                transform.location.y -= speed * deltaTime;
            if (event.key.keysym.sym == SDLK_SPACE)
                transform.location.y += speed * deltaTime;
        }

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
#include "control.h"

void Control::keyDown(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_w:
        cameraPos.y += 0.1f;
        break;
    case SDLK_s:
        cameraPos.y -= 0.1f;
        break;
    case SDLK_a:
        cameraPos.x -= 0.1f;
        break;
    case SDLK_d:
        cameraPos.x += 0.1f;
        break;
    case SDLK_q:
        cameraScale += 1;
        break;
    case SDLK_e:
        cameraScale -= 1;
        if (cameraScale < 1)
            cameraScale = 1;
        break;
    default:
        break;
    }
}
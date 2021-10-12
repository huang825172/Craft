#pragma once

#include "../misc/coord.h"

#include <SDL2/SDL.h>

class Control
{
public:
    Vec2f cameraPos = {0, 0};
    float cameraScale = 1;

    void keyDown(SDL_Event);
};
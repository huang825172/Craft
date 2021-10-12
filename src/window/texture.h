#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
private:
    SDL_Surface *picture;

public:
    SDL_Texture *texture;

    Texture(SDL_Renderer *renderer, const char *path);
    ~Texture();
};
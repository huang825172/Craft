#include "texture.h"

Texture::Texture(SDL_Renderer *renderer, const char *path)
{
    picture = IMG_Load(path);
    texture = SDL_CreateTextureFromSurface(renderer, picture);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(picture);
}
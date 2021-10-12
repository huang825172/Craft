#pragma once

#include "control.h"
#include "../world/world.h"
#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <map>

class Renderer
{
public:
    SDL_Renderer *SDLRenderer;
    int screenWidth;
    int screenHeight;
    std::shared_ptr<Control> control;
    std::shared_ptr<World> world;
    std::map<Block::Type, std::unique_ptr<Texture>> textures;

    Renderer(
        SDL_Renderer *,
        unsigned int, unsigned int,
        std::shared_ptr<Control>,
        std::shared_ptr<World>);
    ~Renderer();

    void clear(SDL_Color);
    void swap();
    void render();

private:
    void loadTextures();
};
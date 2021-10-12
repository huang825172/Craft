#pragma once

#include "../world/world.h"
#include "control.h"
#include "renderer.h"

#include <SDL2/SDL.h>
#include <memory>
#include <map>

constexpr auto windowWidth = 640;
constexpr auto windowHeight = 640;
constexpr auto targetFrameRate = 60;

typedef void (Control::*HandlerFunction)(SDL_Event);

class Window
{
public:
    SDL_Window *SDLWindow;
    SDL_Renderer *SDLRenderer;
    std::shared_ptr<Control> control;
    std::shared_ptr<World> world;
    std::unique_ptr<Renderer> renderer;
    std::map<Uint32, HandlerFunction> handlers;

    Window();
    ~Window();

    void mainLoop(bool);

private:
    void registerHandler(Uint32, HandlerFunction);
};
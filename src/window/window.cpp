#include "window.h"

#include <algorithm>
#include <chrono>

Window::Window()
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) != 0);
    SDLWindow = SDL_CreateWindow(
        "Craft",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth, windowHeight,
        0);
    SDL_assert(SDLWindow);
    SDLRenderer = SDL_CreateRenderer(
        SDLWindow,
        -1,
        SDL_RENDERER_SOFTWARE);
    SDL_assert(SDLRenderer);

    control = std::make_shared<Control>();
    registerHandler(SDL_KEYDOWN, &Control::keyDown);

    world = std::make_shared<World>();

    renderer = std::make_unique<Renderer>(
        SDLRenderer,
        windowWidth, windowHeight,
        control,
        world);
}

Window::~Window()
{
    SDL_DestroyWindow(SDLWindow);
    SDL_Quit();
}

void Window::registerHandler(Uint32 eventType, HandlerFunction handler)
{
    handlers.insert(std::pair<Uint32, HandlerFunction>(eventType, handler));
}

void Window::mainLoop(bool logDefault)
{
    auto quit = false;
    SDL_Event event;
    const auto targetDeltaTime = 1000.0 / targetFrameRate;
    while (!quit)
    {
        auto startTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = true;
            if (logDefault && handlers.count(event.type) == 0)
            {
                SDL_Log("Event type: %d", event.type);
            }
            auto eventHandlers = handlers.equal_range(event.type);
            auto controlInstance = control.get();
            auto executor = [controlInstance, event](std::pair<Uint32, HandlerFunction> handler)
            { (controlInstance->*handler.second)(event); };
            std::for_each(eventHandlers.first, eventHandlers.second, executor);
        }
        renderer->render();
        auto endTime = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (duration == 0)
        {
            SDL_Delay(targetDeltaTime);
        }
        else if (duration < targetDeltaTime)
        {
            SDL_Delay(targetDeltaTime - duration);
        }
        else {
            SDL_Log("FrameTime Critical: %d ms", duration);
        }
    }
}
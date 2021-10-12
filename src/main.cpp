#include "window/window.h"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
    std::make_unique<Window>()->mainLoop(false);
    return 0;
}

#include "App.h"

#include <SDL.h>

#include <cstdio>
#include <exception>

int main(int, char**)
{
    try {
        App app;
        return app.Run();
    }
    catch (const std::exception& exception) {
        std::fprintf(stderr, "3D Reversi: %s\n", exception.what());
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "3D Reversi", exception.what(), nullptr);
        return 1;
    }
}

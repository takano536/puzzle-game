#include <SDL2/SDL.h>

#include "Application/Application.hpp"

int SDL_main(int argc, char *argv[]) {
    SDL_Log("%d:%s", argc, argv[0]);

    Application app;
    if (app.init() != 0) {
        return -1;
    }

    while (!app.should_quit()) {
        app.run();
    }

    app.deinit();
    return 0;
}
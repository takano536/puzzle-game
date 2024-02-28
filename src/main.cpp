#include <SDL2/SDL.h>

#include <string>

#include "Application/Application.hpp"

int SDL_main(int argc, char *argv[]) {
    static_cast<void>(argc), static_cast<void>(argv);

    Application app;
    if (app.init() != 0) {
        return -1;
    }

    while (!app.is_running()) {
        app.run();
    }

    app.deinit();
    return 0;
}
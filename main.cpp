#include <SDL.h>

#include "Application/Application.hpp"

int SDL_main(int argc, char *argv[]) {
    Application app;
    if (app.init() != 0) {
        return -1;
    }
    app.run();
    app.deinit();
    return 0;
}
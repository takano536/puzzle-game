#include <SDL2/SDL.h>

#include "Application/Application.hpp"

int SDL_main(int argc, char *argv[]) {
    std::string args;
    for (int i = 0; i < argc; i++) {
        args += argv[i];
        args += " ";
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "args: %s", args.c_str());

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
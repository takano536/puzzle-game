#pragma once

#include <SDL2/SDL.h>

#include <vector>

class ColorGradator final {
  public:
    std::vector<SDL_Color> gradate(const SDL_Color &left, const SDL_Color &right, int step);
};
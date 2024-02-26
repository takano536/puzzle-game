#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "../../Object.hpp"
#include "../Wall.hpp"

class WallManager : public Object {
  public:
    WallManager();
    virtual ~WallManager() = default;
    void add(SDL_Point coord);
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

  private:
    std::vector<Wall> walls;
};
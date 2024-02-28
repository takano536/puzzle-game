#pragma once

#include <SDL2/SDL.h>

#include "../Object.hpp"

class Wall : public Object {
  public:
    Wall(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color);
    virtual ~Wall() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    static const int RADIUS;

    SDL_Rect rect;
    SDL_Color color;
};

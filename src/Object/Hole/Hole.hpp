#pragma once

#include "../Object.hpp"

class Hole : public Object {
  public:
    Hole(SDL_Point coord, SDL_Point size, SDL_Color color);
    virtual ~Hole() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    SDL_Rect rect;
    SDL_Color color;
};
#pragma once

#include "../Object.hpp"

class Goal : public Object {
  public:
    Goal(SDL_Point coord, SDL_Point size, SDL_Color color);
    virtual ~Goal() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    SDL_Rect rect;
    SDL_Color color;
};
#pragma once

#include "../Object.hpp"

class Floor : public Object {
  public:
    Floor(SDL_Point coord, SDL_Point size, SDL_Color color);
    virtual ~Floor() = default;
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

  private:
    SDL_Rect rect;
    SDL_Color color;
};
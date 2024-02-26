#pragma once

#include "../Object.hpp"

class Player : public Object {
  public:
    Player();
    virtual ~Player() = default;
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

  private:
    void move();
    SDL_FRect rect;
};
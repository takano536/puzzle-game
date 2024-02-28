#pragma once

#include "../Object.hpp"

class Player : public Object {
  public:
    Player(SDL_Point coord, SDL_Point size, SDL_Color color, int speed);
    virtual ~Player() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    void move();

    SDL_Rect rect;
    SDL_Color color;
    int speed;
};
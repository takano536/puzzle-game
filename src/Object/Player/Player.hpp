#pragma once

#include <SDL2/SDL.h>

#include <array>
#include <tuple>
#include <vector>

#include "../../Define/Define.hpp"
#include "../Object.hpp"

class Player : public Object {
  public:
    Player(SDL_Point coord, SDL_Point size, SDL_Color color, int speed);
    virtual ~Player() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    static const std::array<std::tuple<Define::DIRECTION, std::vector<SDL_KeyCode>, SDL_Point>, 4> KEY_MAPS;

    SDL_Rect rect;
    SDL_Color color;
    int speed;

    void move();
};
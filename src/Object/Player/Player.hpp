#pragma once

#include <SDL2/SDL.h>

#include <map>
#include <vector>

#include "../../Define/Define.hpp"
#include "../Object.hpp"

class Player : public Object {
  public:
    Player(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color, int speed);
    virtual ~Player() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    static const std::map<Define::DIRECTION, std::vector<SDL_KeyCode>> KEY_MAPS;
    static const std::map<Define::DIRECTION, SDL_Point> MOVING_DIRS;

    SDL_Rect rect;
    SDL_Point cell_size;
    SDL_Color color;
    Define::DIRECTION moving_dir;
    SDL_Point dest;
    int speed;

    void move();
    void update_dest();
};
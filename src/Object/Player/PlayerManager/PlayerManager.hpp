#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../../Define/Define.hpp"
#include "../../Object.hpp"
#include "../Player.hpp"

class PlayerManager : public Object {
  public:
    PlayerManager(bool is_slip = false);
    virtual ~PlayerManager() = default;
    void add(const SDL_Point &coord, const SDL_Point &player_size, const SDL_Point &cell_size, const SDL_Color &color, int speed);
    void update() override;
    void draw(SDL_Renderer *renderer) const override;
    void set_object_positions(const std::vector<std::vector<Define::CELL_TYPE>> &object_positions);

  private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::vector<Define::CELL_TYPE>> object_positions;
    bool is_slip;
};
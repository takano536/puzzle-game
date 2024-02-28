#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../Object.hpp"
#include "../Player.hpp"

class PlayerManager : public Object {
  public:
    PlayerManager();
    virtual ~PlayerManager() = default;
    void add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color, int speed);
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

  private:
    std::vector<std::unique_ptr<Player>> Players;
};
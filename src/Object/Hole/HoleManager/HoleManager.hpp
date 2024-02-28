#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../Object.hpp"
#include "../Hole.hpp"

class HoleManager : public Object {
  public:
    HoleManager();
    virtual ~HoleManager() = default;
    void add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color);
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;

  private:
    std::vector<std::unique_ptr<Hole>> Holes;
};
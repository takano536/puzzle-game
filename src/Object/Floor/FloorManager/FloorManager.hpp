#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../Object.hpp"
#include "../Floor.hpp"

class FloorManager : public Object {
  public:
    FloorManager();
    virtual ~FloorManager() = default;
    void add(const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color);
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    std::vector<std::unique_ptr<Floor>> Floors;
};
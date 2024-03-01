#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../Define/Define.hpp"
#include "../Floor/Floor.hpp"
#include "../Object.hpp"

class ObjectManager : public Object {
  public:
    ObjectManager();
    virtual ~ObjectManager() = default;
    void add(Define::CELL_TYPE object_type, const SDL_Point &coord, const SDL_Point &size, const SDL_Color &color);
    void update() override;
    void draw(SDL_Renderer *renderer) const override;

  private:
    std::vector<std::unique_ptr<Object>> objects;
};
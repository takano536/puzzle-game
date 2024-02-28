#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Object {
  public:
    Object() = default;
    virtual ~Object() = default;
    virtual void update() = 0;
    virtual void draw(SDL_Renderer *renderer) const = 0;
};
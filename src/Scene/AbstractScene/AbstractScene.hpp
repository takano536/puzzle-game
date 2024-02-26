#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../IOnChangedListener.hpp"
#include "../Parameter/Parameter.hpp"

class IOnChangedListener;

/**
 * @brief シーンの抽象クラス
 */
class AbstractScene {
  public:
    AbstractScene(IOnChangedListener *listener, const Parameter &params);
    virtual ~AbstractScene() = default;

    virtual void update(const SDL_Event &event) = 0;
    virtual void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const = 0;

  protected:
    IOnChangedListener *listener;
};
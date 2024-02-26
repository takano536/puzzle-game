#pragma once

#include <SDL.h>

#include <memory>

#include "../IOnChangedListener.hpp"
#include "../Parameter/Parameter.hpp"

class IOnChangedListener;

/**
 * @brief シーンの抽象クラス
 */
class AbstractScene {
  public:
    AbstractScene(IOnChangedListener *listener, const Parameter &param);
    virtual ~AbstractScene() = default;

    virtual void update() = 0;
    virtual void draw(SDL_Renderer *renderer) const = 0;
    virtual void on_changed(const IOnChangedListener *listener) = 0;
    virtual void set_param(const Parameter param) = 0;

  protected:
    std::unique_ptr<IOnChangedListener> listener;
};
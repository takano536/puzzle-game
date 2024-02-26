#pragma once

#include <SDL.h>

#include "../AbstractScene/AbstractScene.hpp"

/**
 * @brief タイトルシーン
 */
class TitleScene : public AbstractScene {
  public:
    TitleScene(IOnChangedListener *listener, const Parameter &param);
    ~TitleScene() = default;
    void update() override;
    void draw(SDL_Renderer *renderer) const override;
    void on_changed(const IOnChangedListener *listener) override;
    void set_param(const Parameter param) override;
};
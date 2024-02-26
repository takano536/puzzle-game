#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../AbstractScene/AbstractScene.hpp"

/**
 * @brief タイトルシーン
 */
class TitleScene : public AbstractScene {
  public:
    TitleScene(IOnChangedListener *listener, const Parameter &params);
    ~TitleScene() = default;
    void update() override;
    void draw(SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font) const override;
};